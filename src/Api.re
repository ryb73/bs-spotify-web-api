open Js.Promise;
open Belt.Result;
open Types;
open Superagent;

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

let buildGet = (accessToken, path) =>
    get("https://api.spotify.com/v1" ++ path)
    |> setHeader(Authorization(Bearer, accessToken));

/** (accessToken, path) => request */
let buildPut = (accessToken, path) =>
    put("https://api.spotify.com/v1" ++ path)
    |> setHeader(Authorization(Bearer, accessToken));

let decodeResponse = (decoder, body) =>
    switch (decoder(body)) {
        | Ok(decoded) => decoded
        | Error(err) => raise(UnrecognizedResponseFormat(err))
    };

let sendReq = (decoder, request) =>
    request
    |> end_
    |> then_(({ body } as resp) =>
        switch body {
            | Some(body) => body
                |> decodeResponse(decoder)
                |> resolve
            | None => raise(NoBody(resp))
        }
    );

let req = (accessToken, path, decoder) =>
    buildGet(accessToken, path)
    |> sendReq(decoder);

let setOptionalQueryParam = (key, value, req) =>
    switch value {
        | Some(value) => query(key, value, req)
        | None => req
    };

let setOptionalParam = (key, value, req) =>
    switch value {
        | Some(value) => sendKV(key, value, req)
        | None => req
    };
