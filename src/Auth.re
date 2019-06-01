open Superagent;
open PromEx;

[@decco]
type tokens = {
    access_token: string,
    refresh_token: option(string),
    expires_in: int
};

type scope =
    | UserLibraryRead | UserLibraryModify | PlaylistReadPrivate | PlaylistModifyPublic
    | PlaylistModifyPrivate | PlaylistReadCollaborative | UserReadRecentlyPlayed
    | UserTopRead | UserReadPrivate | UserReadEmail | UserReadBirthdate
    | UserReadPlaybackState | UserReadCurrentlyPlaying | Streaming | AppRemoteControl
    | UserModifyPlaybackState | UserFollowModify | UserFollowRead;

let _singleScopeToStr = fun
    | UserLibraryRead => "user-library-read"
    | UserLibraryModify => "user-library-modify"
    | PlaylistReadPrivate => "playlist-read-private"
    | PlaylistModifyPublic => "playlist-modify-public"
    | PlaylistModifyPrivate => "playlist-modify-private"
    | PlaylistReadCollaborative => "playlist-read-collaborative"
    | UserReadRecentlyPlayed => "user-read-recently-played"
    | UserTopRead => "user-top-read"
    | UserReadPrivate => "user-read-private"
    | UserReadEmail => "user-read-email"
    | UserReadBirthdate => "user-read-birthdate"
    | UserReadPlaybackState => "user-read-playback-state"
    | UserReadCurrentlyPlaying => "user-read-currently-playing"
    | Streaming => "streaming"
    | AppRemoteControl => "app-remote-control"
    | UserModifyPlaybackState => "user-modify-playback-state"
    | UserFollowModify => "user-follow-modify"
    | UserFollowRead => "user-follow-read";

let scopeToStr = (scope) =>
    scope
    |> Js.Array.map(_singleScopeToStr)
    |> Js.Array.joinWith(",");

// (~state=?, ~forceShowDialog=?, clientId, redirectUri, scope, responseType) => url
let createAuthorizeUrl =
    (~state=?, ~forceShowDialog=?, clientId, redirectUri, scope, responseType) => {
        let queryParams = Js.Dict.fromList([
            ("client_id", Js.Json.string(clientId)),
            ("redirect_uri", Js.Json.string(redirectUri)),
            ("scope", scope |> Access.scopeToString |> Js.Json.string),
            ("response_type", switch responseType {
                | `Token => Js.Json.string("token")
                | `Code => Js.Json.string("code")
            }),
        ]);

        state
        -> Belt.Option.map(Js.Json.string)
        -> Belt.Option.map(Js.Dict.set(queryParams, "state"));

        forceShowDialog
        -> Belt.Option.map(Js.Json.boolean)
        -> Belt.Option.map(Js.Dict.set(queryParams, "show_dialog"));

        "https://accounts.spotify.com/authorize?" ++ Qs.stringify(queryParams);
};

/** (clienetId, secret, code, redirectUri) => tokens */
let getTokensFromCode = (clientId, secret, code,  redirectUri) => {
    let reqData = [|
        ("client_id", clientId),
        ("client_secret", secret),
        ("grant_type", "authorization_code"),
        ("code", code),
        ("redirect_uri", redirectUri)
    |]
    |> Js.Dict.fromArray
    |> Js.Dict.map([@bs] ((s) => Js.Json.string(s)))
    |> Js.Json.object_;

    post("https://www.googleapis.com/oauth2/v4/token")
    |> setHeader(ContentType(ApplicationXWwwFormUrlencoded))
    |> send(reqData)
    |> end_
    |> map(({ body }) => body
        |> Belt.Option.getExn
        |> tokens_decode
    )
    |> unwrapResult;
    };

/** (clienetId, secret, code, redirectUri) => tokens */
let getTokensFromCode = (clientId, secret, code,  redirectUri) => {
    let reqData = [|
        ("client_id", clientId),
        ("client_secret", secret),
        ("grant_type", "authorization_code"),
        ("code", code),
        ("redirect_uri", redirectUri)
    |]
    |> Js.Dict.fromArray
    |> Js.Dict.map([@bs] ((s) => Js.Json.string(s)))
    |> Js.Json.object_;

    post("https://accounts.spotify.com/api/token")
    |> setHeader(ContentType(ApplicationXWwwFormUrlencoded))
    |> send(reqData)
    |> end_
    |> map(({ body }) => body
        |> Belt.Option.getExn
        |> tokens_decode
    )
    |> unwrapResult;
};
