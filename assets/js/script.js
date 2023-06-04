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
}, 33);

window.addEventListener("resize", () => {
  app.renderer.resize(window.innerWidth, window.innerHeight);
});
