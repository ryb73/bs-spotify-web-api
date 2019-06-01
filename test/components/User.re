open React;
open ReactLib;
open PromEx;
open Spotify;

type user =
  | Me
  | UserId(string);

[@react.component]
let make = (~token) => {
    let (user, setUser) = useState(_ => Me);
    let (gpLimit, setGpLimit) = useState(_ => 10);
    let (gpOffset, setGpOffset) = useState(_ => 0);

    let idChanged = (e) =>
        getTargetValue(e)
        |> (v => setUser(_ => UserId(v)));

    let gpLimitChanged = (e) =>
        getTargetValue(e)
        |> (v => setGpLimit(_ => int_of_string(v)));

    let gpOffsetChanged = (e) =>
        getTargetValue(e)
        |> (v => setGpOffset(_ => int_of_string(v)));

    let doGet = (_) =>
        switch user {
            | Me => Users.me(token)
                |> map(Js.log);

            | UserId(_) => failwith("not implemented")
        } |> ignore;

    let doGetPlaylists = (_) => {
        switch user {
            | Me => Users.getMyPlaylists(~limit=gpLimit, ~offset=gpOffset, token)
            | UserId(id) =>
                Users.getPlaylists(~limit=gpLimit, ~offset=gpOffset, token, id)
        }
        |> map(Js.log);
        ();
    };

    let meClicked = (_) => setUser(_ => Me);
    let otherClicked = (_) => setUser(_ => UserId(""));

    <form className="col card" onSubmit=noopSubmit>
        <h2>(s2e("User"))</h2>

        <div>
            <label>
                <input type_="radio" name="user" value="me"
                    checked={user == Me} onChange=meClicked />
                (s2e("Me"))
            </label>
            <label>
                <input type_="radio" name="user" value="other"
                    checked={user != Me} onChange=otherClicked />
                (s2e("Other User"))
            </label>

            (switch user {
                | Me => null
                | UserId(id) =>
                    <input type_="text" value=id placeholder="user id"
                        onChange=idChanged />
            })
        </div>

        <div><button onClick=doGet>(s2e("Get"))</button></div>

        <div>
            <button onClick=doGetPlaylists>
                (s2e("Get Playlists"))
            </button>

            <input type_="text" placeholder="limit" style=width("48px")
                value=string_of_int(gpLimit) onChange=gpLimitChanged />
            <input type_="text" placeholder="offset" style=width("48px")
                value=string_of_int(gpOffset) onChange=gpOffsetChanged />
        </div>
    </form>;
};
