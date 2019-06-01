open PromEx;
open Superagent;

[@decco]
type tokens = {
    access_token: string,
    refresh_token: option(string),
    expires_in: int
};

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

/** (clientId, secret, code, redirectUri) => tokens */
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
