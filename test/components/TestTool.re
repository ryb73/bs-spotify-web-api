let component = ReasonReact.statelessComponent("TestTool");
let make = (~token, _) => {
    ...component,

    render: (_) =>
        <div className="grid-6">
            <User token />
            <Playlist token />
            <PlaybackTest token />
        </div>
};