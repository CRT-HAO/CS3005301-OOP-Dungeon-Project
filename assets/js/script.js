// let app = new PIXI.Application({
//   width: 256, // default: 800 宽度
//   height: 256, // default: 600 高度
//   antialias: true, // default: false 反锯齿
//   transparent: false, // default: false 透明度
//   resolution: 1, // default: 1 分辨率
// });

// app.renderer.background.color = 0xffffff;
// app.renderer.view.style.position = "absolute";
// app.renderer.view.style.display = "block";
// app.renderer.autoResize = true;
// app.renderer.resize(window.innerWidth, window.innerHeight);

// // document.body.appendChild(app.view);

// // Create the sprite and add it to the stage
// let sprite = PIXI.Sprite.from("image/github.png");
// app.stage.addChild(sprite);

// // Add a ticker callback to move the sprite back and forth
// let elapsed = 0.0;
// app.ticker.add((delta) => {
//   elapsed += delta;
//   sprite.x = 100.0 + Math.cos(elapsed / 50.0) * 100.0;
// });

// async function gameLoop() {
//     //Call this `gameLoop` function on the next screen refresh
//     //(which happens 60 times per second)
//     requestAnimationFrame(gameLoop);
// }

// //Start the loop
// gameLoop();

const block_size = 12;

let timer = window.setInterval(async () => {
  await logic();
  await render();
  let view = await getView();
  $("#view").empty();
  view.objects.forEach((object) => {
    let e = $(`<div class="block"></div>`)
      .css("width", `${block_size}px`)
      .css("height", `${block_size}px`)
      .css("background-color", object.asset == 2 ? "#000000" : "gray")
      .css("top", `${block_size * object.position.y}px`)
      .css("left", `${block_size * object.position.x}px`);
    $("#view").append(e);
  });
}, 16);

window.addEventListener("resize", () => {
  app.renderer.resize(window.innerWidth, window.innerHeight);
});

setKey = (e, value) => {
  let ascii,
    key = e.key;
  if (key.length == 1) {
    ascii = key.charCodeAt(0);
    if (ascii < 128 && e.ctrlKey) {
      ascii = ascii & 0x1f;
    }
  }
  if (typeof ascii == "number" && ascii < 128) {
    setKeyInput(ascii, value);
    // console.log(`ASCII code ${ascii} entered from keyboard`);
  }
};

document.addEventListener("keydown", (e) => setKey(e, true), false);
document.addEventListener("keyup", (e) => setKey(e, false), false);
