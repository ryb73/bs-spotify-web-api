open ReactLib;
open PromiseEx;

type state =
  | Me
  | UserId(string);

type action =
  | SetMe
  | SetUserId(string);

let onIdChanged = (e, { ReasonReact.send }) =>
    send(SetUserId(ReactEvent.Form.currentTarget(e)##value));

let renderIdField = ({ ReasonReact.state, handle }) =>
    switch state {
        | Me => ReasonReact.null
        | UserId(id) => <input type_="text" value=id onChange=(handle(onIdChanged)) />
    };

let meClicked = (_, { ReasonReact.send }) => send(SetMe);

let otherClicked = (_, { ReasonReact.send }) => send(SetUserId(""));

let component = ReasonReact.reducerComponent("User");
let make = (~token, _) => {
    let doGet = (_, { ReasonReact.state }) =>
        switch state {
            | Me =>
                Users.me(token)
                    |> map(Js.log);

            | UserId(_) => failwith("not implemented")
        } |> ignore;

    {
        ...component,

        render: ({ handle } as self) =>
            <form className="col card" onSubmit=noopSubmit>
                <div>
                    <h2>(s2e("User"))</h2>
                    <label>
                        <input type_="radio" name="user" value="me"
                            onClick=(handle(meClicked)) />
                        (s2e("Me"))
                    </label>
                    <label>
                        <input type_="radio" name="user" value="other"
                            onClick=(handle(otherClicked)) />
                        (s2e("Other User"))
                    </label>
                    (renderIdField(self))
                </div>
                <div><button onClick=(handle(doGet))>(s2e("Get"))</button></div>
            </form>,

        initialState: (_) => Me,

        reducer: (action, _) => ReasonReact.(
            switch action {
                | SetMe => Update(Me)
                | SetUserId(id) => Update(UserId(id))
            }
        ),
    }
};
