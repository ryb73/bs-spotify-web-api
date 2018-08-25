/* class



class type body 'a = {
    pub body : Js.t 'a;
}; */

open Types.User;

let me = (accessToken) => Api.req(accessToken, "/me", t_decode);

let getPlaylists = (~limit=?, ~offset=?, accessToken, userId) => {
    "/users/" ++ ReDom.encodeUriComponent(userId) ++ "/playlists"
        |> Api.buildReq(accessToken)
        |> Api.setOptionalParam("limit", limit |> Belt.Option.map(_, string_of_int))
        |> Api.setOptionalParam("offset", offset |> Belt.Option.map(_, string_of_int))
        |> Api.sendReq(Api.page_decode(Types.Playlist.t_decode));
};