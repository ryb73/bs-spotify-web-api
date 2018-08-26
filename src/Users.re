open Types.User;

let me = (accessToken) => Api.req(accessToken, "/me", t_decode);

let _getPlaylists = (~limit=?, ~offset=?, accessToken, path) =>
    path
        |> Api.buildReq(accessToken)
        |> Api.setOptionalParam("limit", limit |> Belt.Option.map(_, string_of_int))
        |> Api.setOptionalParam("offset", offset |> Belt.Option.map(_, string_of_int))
        |> Api.sendReq(Api.page_decode(Types.Playlist.t_decode));

let playlistsMax = 100;
let getPlaylists = (~limit=?, ~offset=?, accessToken, userId) => {
    "/users/" ++ ReDom.encodeUriComponent(userId) ++ "/playlists"
        |> _getPlaylists(~limit?, ~offset?, accessToken);
};

let getMyPlaylists = (~limit=?, ~offset=?, accessToken) =>
    "/me/playlists"
        |> _getPlaylists(~limit?, ~offset?, accessToken);