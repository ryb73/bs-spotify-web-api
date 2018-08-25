open Js.Promise;
open Belt.Result;
open Spotify;

[@decco]
type page('a) = {
    href: string,
    items: array('a),
    limit: int,
    next: option(string),
    offset: int,
    previous: option(string),
    total: int,
};

let buildReq = (accessToken, path) => Superagent.(
    get("https://api.spotify.com/v1" ++ path)
        |> setHeader(Authorization(Bearer, accessToken))
);

let decodeResponse = (decoder, body) =>
    switch (decoder(body)) {
        | Ok(decoded) => decoded
        | Error(err) => raise(UnrecognizedResponseFormat(err))
    };

let sendReq = (decoder, request) => Superagent.(
    request
        |> end_
        |> then_(({ body } as resp) =>
            switch body {
                | Some(body) => body
                    |> decodeResponse(decoder)
                    |> resolve
                | None => raise(NoBody(resp))
            }
        )
);

let req = (accessToken, path, decoder) =>
    buildReq(accessToken, path)
        |> sendReq(decoder);

let setOptionalParam = (key, value, req) =>
    switch value {
        | Some(value) => Superagent.query(key, value, req)
        | None => req
    };