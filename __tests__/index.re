open Jest;
open Expect;
open Spotify;

describe("Auth", () => {
    test("createAuthorizeUrl", () =>
        Auth.createAuthorizeUrl(
            ~state="stt", ~forceShowDialog=true, "cli", "http://uri.com/",
            Access.(scope |> withStreaming), `Code
        )
        |> expect
        |> toBe("https://accounts.spotify.com/authorize?client_id=cli&redirect_uri=http%3A%2F%2Furi.com%2F&scope=streaming&response_type=code&state=stt&show_dialog=true")
    );
});
