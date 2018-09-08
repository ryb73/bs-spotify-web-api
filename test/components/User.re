open ReactLib;
open PromiseEx;
open ReasonReact;

type user =
  | Me
  | UserId(string);

type state = {
    user: user,
    gpLimit: int,
    gpOffset: int
};

type action =
  | SetMe
  | SetUserId(string)
  | SetGpLimit(int)
  | SetGpOffset(int);

let idChanged = (e, { send }) =>
    send(SetUserId(ReactEvent.Form.currentTarget(e)##value));

let gpLimitChanged = (e, { send }) =>
    send(SetGpLimit(int_of_string(ReactEvent.Form.currentTarget(e)##value)));

let gpOffsetChanged = (e, { send }) =>
    send(SetGpOffset(int_of_string(ReactEvent.Form.currentTarget(e)##value)));

let meClicked = (_, { send }) => send(SetMe);
let otherClicked = (_, { send }) => send(SetUserId(""));

let renderIdField = ({ state, handle }) =>
    switch state.user {
        | Me => null
        | UserId(id) => <input type_="text" value=id onChange=(handle(idChanged)) />
    };

let component = reducerComponent("User");
let make = (~token, _) => {
    let doGet = (_, { state }) =>
        switch state.user {
            | Me => Users.me(token)
                |> map(Js.log);

            | UserId(_) => failwith("not implemented")
        } |> ignore;

    let doGetPlaylists = (_, { state: { user, gpLimit, gpOffset } }) => {
        switch user {
            | Me => Users.getMyPlaylists(~limit=gpLimit, ~offset=gpOffset, token)
            | UserId(id) => Users.getPlaylists(~limit=gpLimit, ~offset=gpOffset, token, id)
        }
        |> map(Js.log);
        ();
    };

    {
        ...component,

        render: ({ handle, state: { user, gpLimit, gpOffset } } as self) =>
            <form className="col card" onSubmit=noopSubmit>
                <h2>(s2e("User"))</h2>

                <div>
                    <label>
                        <input type_="radio" name="user" value="me"
                            checked={user == Me} onChange=(handle(meClicked)) />
                        (s2e("Me"))
                    </label>
                    <label>
                        <input type_="radio" name="user" value="other"
                            checked={user != Me} onChange=(handle(otherClicked)) />
                        (s2e("Other User"))
                    </label>
                    (renderIdField(self))
                </div>

                <div><button onClick=handle(doGet)>(s2e("Get"))</button></div>

                <div>
                    <button onClick=handle(doGetPlaylists)>
                        (s2e("Get Playlists"))
                    </button>

                    <input type_="text" placeholder="limit" style=width("48px")
                        value=string_of_int(gpLimit) onChange=handle(gpLimitChanged) />
                    <input type_="text" placeholder="offset" style=width("48px")
                        value=string_of_int(gpOffset) onChange=handle(gpOffsetChanged) />
                </div>
            </form>,

        initialState: (_) => { user: Me, gpLimit: 10, gpOffset: 0 },

        reducer: (action, state) =>
            switch action {
                | SetMe => Update({ ...state, user: Me })
                | SetUserId(id) => Update({ ...state, user: UserId(id) })
                | SetGpLimit(gpLimit) => Update({ ...state, gpLimit })
                | SetGpOffset(gpOffset) => Update({ ...state, gpOffset })
            },
    }
};
