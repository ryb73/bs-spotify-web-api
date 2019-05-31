open Belt.Result;
open ReDom;

[@decco] type hash = {
    access_token: option(string)
};

let getAccessTokenFromHash = () => {
    let parsedHash = Location.hash()
        |> Js.String.substr(~from=1)
        |> Qs.parse
        |> hash_decode;
    switch parsedHash {
        | Ok({ access_token }) => access_token
        | Error(_) => None
    };
};