open ReactLib;
open PromiseEx;
open ReasonReact;

type state = {
    id: string,
    gtLimit: int,
    gtOffset: int
};

type action =
  | SetId(string)
  | SetGtLimit(int)
  | SetGtOffset(int);

let idChanged = (e, { send }) =>
    send(SetId(ReactEvent.Form.currentTarget(e)##value));

let gtLimitChanged = (e, { send }) =>
    send(SetGtLimit(int_of_string(ReactEvent.Form.currentTarget(e)##value)));

let gtOffsetChanged = (e, { send }) =>
    send(SetGtOffset(int_of_string(ReactEvent.Form.currentTarget(e)##value)));

let component = reducerComponent("Playlist");
let make = (~token, _) => {
    let doGetTracks = (_, { state: { id, gtLimit, gtOffset } }) =>
        Playlists.getTracks(~limit=gtLimit, ~offset=gtOffset, token, id)
            |> map(Js.log)
            |> ignore;

    {
        ...component,

        render: ({ handle, state: { id, gtLimit, gtOffset } }) =>
            <form className="col card" onSubmit=noopSubmit>
                <h2>(s2e("Playlist"))</h2>

                <div>
                    <input type_="text" value=id onChange=(handle(idChanged)) />
                </div>

                <div>
                    <button onClick=handle(doGetTracks)>(s2e("GetTracks"))</button>

                    <input type_="text" placeholder="limit" style=width("48px")
                        value=string_of_int(gtLimit) onChange=handle(gtLimitChanged) />
                    <input type_="text" placeholder="offset" style=width("48px")
                        value=string_of_int(gtOffset) onChange=handle(gtOffsetChanged) />
                </div>
            </form>,

        initialState: (_) => { id: "", gtLimit: 10, gtOffset: 0 },

        reducer: (action, state) =>
            switch action {
                | SetId(id) => Update({ ...state, id })
                | SetGtLimit(gtLimit) => Update({ ...state, gtLimit })
                | SetGtOffset(gtOffset) => Update({ ...state, gtOffset })
            },
    }
};
