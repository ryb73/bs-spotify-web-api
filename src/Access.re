type x;
type o;
type userLibraryRead = o;
type userLibraryModify = o;
type playlistReadPrivate = o;
type playlistModifyPublic = o;
type playlistModifyPrivate = o;
type playlistReadCollaborative = o;
type userReadRecentlyPlayed = o;
type userTopRead = o;
type userReadPrivate = o;
type userReadEmail = o;
type userReadBirthdate = o;
type userReadPlaybackState = o;
type userReadCurrentlyPlaying = o;
type streaming = o;
type appRemoteControl = o;
type userModifyPlaybackState = o;
type userFollowModify = o;
type userFollowRead = o;

type scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_) = Js.Array.t(string);

let scope = [||];

let withUserLibraryRead = Js.Array.concat([|"user-library-read"|]);
let withUserLibraryModify = Js.Array.concat([|"user-library-modify"|]);
let withPlaylistReadPrivate = Js.Array.concat([|"playlist-read-private"|]);
let withPlaylistModifyPublic = Js.Array.concat([|"playlist-modify-public"|]);
let withPlaylistModifyPrivate = Js.Array.concat([|"playlist-modify-private"|]);
let withPlaylistReadCollaborative = Js.Array.concat([|"playlist-read-collaborative"|]);
let withUserReadRecentlyPlayed = Js.Array.concat([|"user-read-recently-played"|]);
let withUserTopRead = Js.Array.concat([|"user-top-read"|]);
let withUserReadPrivate = Js.Array.concat([|"user-read-private"|]);
let withUserReadEmail = Js.Array.concat([|"user-read-email"|]);
let withUserReadBirthdate = Js.Array.concat([|"user-read-birthdate"|]);
let withUserReadPlaybackState = Js.Array.concat([|"user-read-playback-state"|]);
let withUserReadCurrentlyPlaying = Js.Array.concat([|"user-read-currently-playing"|]);
let withStreaming = Js.Array.concat([|"streaming"|]);
let withAppRemoteControl = Js.Array.concat([|"app-remote-control"|]);
let withUserModifyPlaybackState = Js.Array.concat([|"user-modify-playback-state"|]);
let withUserFollowModify = Js.Array.concat([|"user-follow-modify"|]);
let withUserFollowRead = Js.Array.concat([|"user-follow-read"|]);

let scopeToString = (scope: scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_)) =>
    Js.Array.joinWith(",", scope);

type token('scope) = string;
let token = (type scope, ~limitScope as _: scope, token: string): token(scope) =>
    Obj.magic(token);
