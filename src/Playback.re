[@bs.set] external setPlaybackSdkReadyListener : ReDomSuite.Window.t => (unit => unit) => unit = "onSpotifyWebPlaybackSDKReady";

let _initialPromise = Js.Promise.make((~resolve, ~reject as _) => {
    setPlaybackSdkReadyListener(ReDom.window, () => {
        let u = ();
        resolve(. u);
    });
});

let init = () => _initialPromise;
