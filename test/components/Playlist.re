open React;
open ReactLib;
open PromEx;
open Spotify;

[@react.component]
let make = (~token) => {
    let (id, setId) = useState(_ => "");
    let (gtLimit, setGtLimit) = useState(_ => 10);
    let (gtOffset, setGtOffset) = useState(_ => 0);

    let doGetTracks = (_) =>
        Playlists.getTracks(~limit=gtLimit, ~offset=gtOffset, token, id)
            |> map(Js.log)
            |> ignore;

    let idChanged = (e) =>
        getTargetValue(e)
        |> (v => setId(_ => v));

    let gtLimitChanged = (e) =>
        getTargetValue(e)
        |> (v => setGtLimit(_ => int_of_string(v)));

    let gtOffsetChanged = (e) =>
        getTargetValue(e)
        |> (v => setGtOffset(_ => int_of_string(v)));

    <form className="col card" onSubmit=noopSubmit>
        <h2>(s2e("Playlist"))</h2>

        <div>
            <input type_="text" value=id placeholder="playlist id"
                onChange=idChanged />
        </div>

        <div>
            <button onClick=doGetTracks>(s2e("GetTracks"))</button>

            <input type_="text" placeholder="limit" style=width("48px")
                value=string_of_int(gtLimit) onChange=gtLimitChanged />
            <input type_="text" placeholder="offset" style=width("48px")
                value=string_of_int(gtOffset) onChange=gtOffsetChanged />
        </div>
    </form>;
};
