open React;
open Belt.Result;
open ReactLib;
open Spotify;

type playerState = {
    player: Playback.player,
    name: string,
    deviceId: string
};

type state = {
    initialized: bool,
    deviceId: string,
    contextUri: string,
    uris: string,
    positionMs: string,
    playerName: string,
    player: option(playerState)
};

type action =
    | SetInitialized
    | SetPlayerName(string)
    | SetDeviceId(string)
    | SetContextUri(string)
    | SetUris(string)
    | SetPositionMs(string)
    | ClearPlayer
    | SetPlayer(Playback.player, string, string);

let displayError = fun
    | Ok({ Playback.message }) => message
    | Error(e) => "couldn't decode error " ++ getOption(Js.Json.stringifyAny(e));

let initialState = {
    initialized: false, deviceId: "", contextUri: "",
    uris: "spotify:track:3PK7tZzJxuoJYoik7j3p1H", positionMs: "",
    playerName: "", player: None
};

let reducer = (state, action) =>
    switch action {
        | SetInitialized => { ...state, initialized: true }
        | SetDeviceId(deviceId) => { ...state, deviceId }
        | SetContextUri(contextUri) => { ...state, contextUri }
        | SetUris(uris) => { ...state, uris }
        | SetPositionMs(positionMs) => { ...state, positionMs }
        | SetPlayerName(playerName) => { ...state, playerName }
        | ClearPlayer => { ...state, player: None }
        | SetPlayer(p, n, d) => {
            ...state, player: Some({
                player: p,
                name: n,
                deviceId: d
            })
        }
    };

[@react.component]
let make = (~token) => {
    let (state, send) = useReducer(reducer, initialState);
    let { deviceId, contextUri, uris, positionMs, playerName, player, initialized }
        = state;

    useEffect0(() => {
        Playback.ensureInitialized()
        |> PromEx.map((_) => send(SetInitialized));
        None;
    });

    let doMakePlayer = (_) => {
        open Playback;

        let player = makePlayer(token, playerName);
        player
        |> onInitializationError((error) => Js.log2("init error", displayError(error)))
        |> onAuthenticationError((error) => Js.log2("auth error", displayError(error)))
        |> onAccountError((error) => Js.log2("acc error", displayError(error)))
        |> onPlaybackError((error) => Js.log2("bak error", displayError(error)))
        |> onNotReady((result) => Js.log2("not ready", result))
        |> onPlayerStateChanged(fun
            | Ok(None) => send(ClearPlayer)
            | Ok(Some(state)) => Js.log2("state changed", state)
            | error => Js.log2("state error", error)
        )
        |> onReady(fun
            | Ok({ device_id }) => send(SetPlayer(player, playerName, device_id))
            | error => Js.log2("ready but error", error)
        )
        |> connect;
    };

    let doPlay = (_) => {
        let deviceId = deviceId == "" ? None : Some(deviceId);
        let positionMs = positionMs == "" ? None : Some(int_of_string(positionMs));

        switch (contextUri, uris) {
            | ("", "") => Playback.play(~deviceId?, ~positionMs?, token)
            | (context, "") => Playback.playContext(~deviceId?, ~positionMs?, token, context)
            | (_, uris) => {
                let uris = Js.String.split(",", uris);
                Playback.playUris(~deviceId?, ~positionMs?, token, uris);
            }
        };
        ();
    };

    let deviceIdChanged = (e) =>
        send(SetDeviceId(ReactEvent.Form.currentTarget(e)##value));

    let contextUriChanged = (e) =>
        send(SetContextUri(ReactEvent.Form.currentTarget(e)##value));

    let urisChanged = (e) =>
        send(SetUris(ReactEvent.Form.currentTarget(e)##value));

    let positionMsChanged = (e) =>
        send(SetPositionMs(ReactEvent.Form.currentTarget(e)##value));

    let playerNameChanged = (e) =>
        send(SetPlayerName(ReactEvent.Form.currentTarget(e)##value));

    let disconnectPlayer = (_) => {
        let player = getOption(player).player;
        Playback.disconnect(player);
    };

    let activePlayer =
        switch player {
            | Some({ name, deviceId }) =>
                <div>
                    <div>(s2e("Active player: " ++ name))</div>
                    <div>(s2e("Device ID: " ++ deviceId))</div>
                    <div>
                        <button onClick=disconnectPlayer>(s2e("Disconnect"))</button>
                    </div>
                </div>
            | None => ReasonReact.null
        };

    initialized ?
        <form className="col card" onSubmit=noopSubmit>
            <h2>(s2e("Playback"))</h2>

            <div>
                <button onClick=doMakePlayer>(s2e("MakePlayer"))</button>

                <input type_="text" value=playerName style=(width("125px"))
                    placeholder="player name" onChange=playerNameChanged />
            </div>

            <div>
                <button onClick=doPlay>(s2e("Play"))</button>

                <input type_="text" value=deviceId placeholder="deviceId"
                    onChange=deviceIdChanged />
                <input type_="text" value=contextUri placeholder="contextUri"
                    onChange=contextUriChanged />
                <input type_="text" value=uris placeholder="uris"
                    onChange=urisChanged />
                <input type_="text" value=positionMs placeholder="positionMs"
                    onChange=positionMsChanged />
            </div>

            (activePlayer)
        </form>
    :
        <div>(s2e("initializing"))</div>;
};
