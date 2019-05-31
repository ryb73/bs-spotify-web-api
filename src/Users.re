open Types.User;

let me = (accessToken) => Api.req(accessToken, "/me", t_decode);

let _getPlaylists = (~limit=?, ~offset=?, accessToken, path) =>
    path
        |> Api.buildGet(accessToken)
        |> Api.setOptionalQueryParam("limit", limit |> Belt.Option.map(_, string_of_int))
        |> Api.setOptionalQueryParam("offset", offset |> Belt.Option.map(_, string_of_int))
        |> Api.sendReq(Api.page_decode(Types.Playlist.t_decode));

let playlistsMax = 100;
let getPlaylists = (~limit=?, ~offset=?, accessToken, userId) => {
    "/users/" ++ Js.Global.encodeURIComponent(userId) ++ "/playlists"
        |> _getPlaylists(~limit?, ~offset?, accessToken);
};

let getMyPlaylists = (~limit=?, ~offset=?, accessToken) =>
    "/me/playlists"
        |> _getPlaylists(~limit?, ~offset?, accessToken);