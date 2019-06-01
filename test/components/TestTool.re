[@react.component]
let make = (~token) =>
    <div className="grid-6">
        <User token />
        <Playlist token />
    </div>;
