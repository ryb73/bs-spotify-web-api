let getTracks = (~fields=?, ~limit=?, ~offset=?, ~market=?, accessToken, playlistId) =>
    "/playlists/" ++ ReDom.encodeUriComponent(playlistId) ++ "/tracks"
    |> Api.buildReq(accessToken)
    |> Api.setOptionalParam("fields", fields)
    |> Api.setOptionalParam("limit", limit |> Belt.Option.map(_, string_of_int))
    |> Api.setOptionalParam("offset", offset |> Belt.Option.map(_, string_of_int))
    |> Api.setOptionalParam("market", market)
    |> Api.sendReq(Api.page_decode(Types.PlaylistTrack.t_decode));