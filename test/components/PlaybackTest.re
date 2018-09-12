open Belt.Result;
open ReactLib;
open ReasonReact;

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

let deviceIdChanged = (e, { send }) =>
    send(SetDeviceId(ReactEvent.Form.currentTarget(e)##value));

let contextUriChanged = (e, { send }) =>
    send(SetContextUri(ReactEvent.Form.currentTarget(e)##value));

let urisChanged = (e, { send }) =>
    send(SetUris(ReactEvent.Form.currentTarget(e)##value));

let positionMsChanged = (e, { send }) =>
    send(SetPositionMs(ReactEvent.Form.currentTarget(e)##value));

let playerNameChanged = (e, { send }) =>
    send(SetPlayerName(ReactEvent.Form.currentTarget(e)##value));

let disconnectPlayer = (_, { state: { player }}) => {
    let player = getOption(player).player;
    Playback.disconnect(player);
};

let displayError = fun
    | Ok({ Playback.message }) => message
    | Error(e) => "couldn't decode error " ++ getOption(Js.Json.stringifyAny(e));

let renderActivePlayer = ({ state: { player }, handle }) =>
    switch player {
        | Some({ name, deviceId }) =>
            <div>
                <div>(s2e("Active player: " ++ name))</div>
                <div>(s2e("Device ID: " ++ deviceId))</div>
                <div>
                    <button onClick=handle(disconnectPlayer)>(s2e("Disconnect"))</button>
                </div>
            </div>
        | None => ReasonReact.null
    };

let component = reducerComponent("PlaybackTest");
let make = (~token, _) => {
    let doMakePlayer = (_, { state: { playerName }, send }) => {
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

    let doPlay = (_, { state: { deviceId, contextUri, uris, positionMs }}) => {
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

    {
        ...component,

        didMount: ({ send }) =>
            Playback.ensureInitialized()
                |> PromiseEx.map((_) => send(SetInitialized))
                |> ignore,

        render: self => {
            let { handle,
                  state: { initialized, deviceId, contextUri, uris, positionMs,
                           playerName } } = self;

            initialized ?
                <form className="col card" onSubmit=noopSubmit>
                    <h2>(s2e("Playback"))</h2>

                    <div>
                        <button onClick=handle(doMakePlayer)>(s2e("MakePlayer"))</button>

                        <input type_="text" value=playerName style=(width("125px"))
                            placeholder="player name" onChange=(handle(playerNameChanged)) />
                    </div>

                    <div>
                        <button onClick=handle(doPlay)>(s2e("Play"))</button>

                        <input type_="text" value=deviceId placeholder="deviceId"
                            onChange=(handle(deviceIdChanged)) />
                        <input type_="text" value=contextUri placeholder="contextUri"
                            onChange=(handle(contextUriChanged)) />
                        <input type_="text" value=uris placeholder="uris"
                            onChange=(handle(urisChanged)) />
                        <input type_="text" value=positionMs placeholder="positionMs"
                            onChange=(handle(positionMsChanged)) />
                    </div>

                    (renderActivePlayer(self))
                </form>
            :
                <div>(s2e("initializing"))</div>
        },

        initialState: (_) => {
            initialized: false, deviceId: "", contextUri: "",
            uris: "spotify:track:3PK7tZzJxuoJYoik7j3p1H", positionMs: "",
            playerName: "", player: None
        },

        reducer: (action, state) =>
            switch action {
                | SetInitialized => Update({ ...state, initialized: true })
                | SetDeviceId(deviceId) => Update({ ...state, deviceId })
                | SetContextUri(contextUri) => Update({ ...state, contextUri })
                | SetUris(uris) => Update({ ...state, uris })
                | SetPositionMs(positionMs) => Update({ ...state, positionMs })
                | SetPlayerName(playerName) => Update({ ...state, playerName })
                | ClearPlayer => Update({ ...state, player: None })
                | SetPlayer(p, n, d) => Update({
                    ...state, player: Some({
                        player: p,
                        name: n,
                        deviceId: d
                    })
                })
            },
    }
};
