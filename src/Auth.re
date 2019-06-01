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

// (~state=?, ~forceShowDialog=?, clientId, redirectUri, scope) => url
let createAuthorizeUrl = (~state=?, ~forceShowDialog=?, clientId, redirectUri, scope) => {
    let queryParams = Js.Dict.fromList([
        ("client_id", Js.Json.string(clientId)),
        ("response_type", Js.Json.string("token")),
        ("redirect_uri", Js.Json.string(redirectUri)),
        ("scope", scope |> Access.scopeToString |> Js.Json.string)
    ]);

    switch state {
        | Some(s) => Js.Dict.set(queryParams, "state", Js.Json.string(s))
        | None => ()
    };

    switch forceShowDialog {
        | Some(fsd) => Js.Dict.set(queryParams, "show_dialog", Js.Json.boolean(fsd))
        | None => ()
    };

    "https://accounts.spotify.com/authorize?" ++ Qs.stringify(queryParams);
};