open PromEx;
open Superagent;

[@decco]
type tokens = {
    access_token: string,
    refresh_token: option(string),
    expires_in: int
};

/** (~state=?, ~forceShowDialog=?, clientId, redirectUri, scope, responseType) => url */
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
        -> Belt.Option.map(Js.Dict.set(queryParams, "state"))
        -> ignore;

        forceShowDialog
        -> Belt.Option.map(Js.Json.boolean)
        -> Belt.Option.map(Js.Dict.set(queryParams, "show_dialog"))
        -> ignore;

        "https://accounts.spotify.com/authorize?" ++ Qs.stringify(queryParams);
};

/** (clientId, secret, code, redirectUri) => tokens */
let getTokensFromCode = (clientId, secret, code,  redirectUri) => {
    post("https://accounts.spotify.com/api/token")
    |> type_(`form)
    |> sendKV("client_id", clientId |> Js.Json.string)
    |> sendKV("client_secret", secret |> Js.Json.string)
    |> sendKV("grant_type", "authorization_code" |> Js.Json.string)
    |> sendKV("code", code |> Js.Json.string)
    |> sendKV("redirect_uri", Js.Global.encodeURI(redirectUri) |> Js.Json.string)
    |> end_
    |> map(({ body }) => body
        |> Belt.Option.getExn
        |> tokens_decode
    )
    |> map(Belt.Result.getExn)
};

/** (clientId, secret, refreshToken) => tokens */
let refreshAccessToken = (clientId, secret, refreshToken) =>
    post("https://accounts.spotify.com/api/token")
    |> type_(`form)
    |> sendKV("refresh_token", refreshToken |> Js.Json.string)
    |> sendKV("client_id", clientId |> Js.Json.string)
    |> sendKV("client_secret", secret |> Js.Json.string)
    |> sendKV("grant_type", "refresh_token" |> Js.Json.string)
    |> end_
    |> map(({ body }) => body
        |> Belt.Option.getExn
        |> tokens_decode
    )
    |> map(Belt.Result.getExn);
