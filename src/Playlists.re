open Api;

let tracksMax = 100;

let getTracks = (~fields=?, ~limit=?, ~offset=?, ~market=?, accessToken, playlistId) =>
    "/playlists/" ++ Js.Global.encodeURIComponent(playlistId) ++ "/tracks"
    |> buildGet(accessToken)
    |> setOptionalQueryParam("fields", fields)
    |> setOptionalQueryParam("limit", limit |> Belt.Option.map(_, string_of_int))
    |> setOptionalQueryParam("offset", offset |> Belt.Option.map(_, string_of_int))
    |> setOptionalQueryParam("market", market)
    |> sendReq(page_decode(Types.PlaylistTrack.t_decode));