open Belt.Result;
open PromiseEx;
open Api;

type player;

[@decco] type error = { message: string };
[@decco] type initializationError = error;
[@decco] type authenticationError = error;
[@decco] type accountError = error;
[@decco] type playbackError = error;

[@decco] type webPlaybackPlayer = { device_id: string };

[@decco]
type context = {
    uri: option(string),
    metadata: option(Js.Json.t),
};

[@decco]
type disallows = {
    [@decco.default false] pausing: bool,
    [@decco.default false] peeking_next: bool,
    [@decco.default false] peeking_prev: bool,
    [@decco.default false] resuming: bool,
    [@decco.default false] seeking: bool,
    [@decco.default false] skipping_next: bool,
    [@decco.default false] skipping_prev: bool,
};

[@decco]
type trackWindow = {
    current_track: Js.Json.t,
    previous_tracks: array(Js.Json.t),
    next_tracks: array(Js.Json.t)
};

type repeatMode = NoRepeat | RepeatOnce | RepeatForever;
let repeatMode_encode = (v) =>
    switch v {
        | NoRepeat => 0
        | RepeatOnce => 1
        | RepeatForever => 2
    }
    |> float_of_int
    |> Js.Json.number;
let repeatMode_decode = (j) =>
    switch (Js.Json.classify(j)) {
        | Js.Json.JSONNumber(0.) => Ok(NoRepeat)
        | Js.Json.JSONNumber(1.) => Ok(RepeatOnce)
        | Js.Json.JSONNumber(2.) => Ok(RepeatForever)
        | _ => Decco.error("Invalid enum value", j)
    };

[@decco]
type webPlaybackState = {
    context: context,
    disallows: disallows,
    track_window: trackWindow,
    paused: bool,
    position: int,
    repeat_mode: repeatMode,
    shuffle: bool,
};

[@bs.set] external setPlaybackSdkReadyListener : ReDomSuite.Window.t => (unit => unit) => unit = "onSpotifyWebPlaybackSDKReady";

let _initialPromise = Js.Promise.make((~resolve, ~reject as _) => {
    setPlaybackSdkReadyListener(ReDom.window, () => {
        let u = ();
        resolve(. u);
    });
});

let ensureInitialized = () => _initialPromise;

[@bs.scope "Spotify"] [@bs.new]
external _makePlayer: Js.t({..}) => player = "Player";

let makePlayer = (accessToken, name) =>
    _makePlayer({
        "name": name,
        "getOAuthToken": (cb) => cb(accessToken)
    });

[@bs.send] external connect : player => unit = "";
[@bs.send] external disconnect : player => unit = "";

[@bs.send.pipe: player]
external _addListener : string => (Js.Json.t => unit) => unit = "addListener";

let _listener = (event, decoder, cb, player) => {
    _addListener(event, (res) => {
        Js.log(res);
        cb(decoder(res))
    }, player);
    player;
};

let onInitializationError = _listener("initialization_error", error_decode);
let onAuthenticationError = _listener("authentication_error", error_decode);
let onAccountError = _listener("account_error", error_decode);
let onPlaybackError = _listener("playback_error", error_decode);
let onReady = _listener("ready", webPlaybackPlayer_decode);
let onNotReady = _listener("not_ready", webPlaybackPlayer_decode);
let onPlayerStateChanged = _listener("player_state_changed", Decco.optionFromJson(webPlaybackState_decode));

let _play = (~deviceId=?, ~contextUri=?, ~uris=?, ~positionMs=?, accessToken) => {
    open! Belt.Option;

    let query = "/me/player/play" ++ switch deviceId {
        | Some(s) => "?device_id=" ++ s
        | None => ""
    };

    buildPut(accessToken, query)
    |> setOptionalParam("context_uri", contextUri |> map(_, Js.Json.string))
    |> setOptionalParam("position_ms",
        positionMs
        |> map(_, float_of_int)
        |> map(_, Js.Json.number)
    )
    |> setOptionalParam("uris",
        uris
        |> map(_, Js.Array.map(Js.Json.string))
        |> map(_, Js.Json.array)
    )
    |> Superagent.end_
    |> thenResolve();
};

let play = (~deviceId=?, ~positionMs=?, accessToken) =>
    _play(~deviceId?, ~positionMs?, accessToken);

let playContext = (~deviceId=?, ~positionMs=?, accessToken, contextUri) =>
    _play(~deviceId?, ~positionMs?, ~contextUri, accessToken);

let playUris = (~deviceId=?, ~positionMs=?, accessToken, uris) =>
    _play(~deviceId?, ~positionMs?, ~uris, accessToken);
