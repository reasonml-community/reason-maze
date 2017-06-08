const path = require('path');
const express = require('express');
const app = express();
const fs = require('fs');
const Twit = require('twit');

const twit = new Twit({
  consumer_key: process.env.CONSUMER_KEY,
  consumer_secret: process.env.CONSUMER_SECRET,
  access_token: process.env.ACCESS_TOKEN,
  access_token_secret: process.env.ACCESS_TOKEN_SECRET
})

const TIME_FILE = './lastPostTime'
const hasBeenLongEnough = () => {
  try {
    return Date.now() - +fs.readFileSync(TIME_FILE, 'utf8')  > 1000 * 60 * 25;
  } catch (err) {
    return true
  }
};
const updateLastTime = () => fs.writeFileSync(TIME_FILE, Date.now() + '');

var randomMaze = require('random-maze');

app.get('/', (req, res) => {
  
  res.send(`
<!doctype html>
<title>Reason Maze Bot</title>
<style>
body {
font-family: Helvetica, arial, sans-serif;
padding: 50px;
text-align: center;
}
</style>
<body>
<h1>Reason Maze Bot</h1>
<a href="https://github.com/jaredly/reason-maze">https://github.com/jaredly/reason-maze</a><br/>
<a href="https://twitter.com/reasonmazebot">https://twitter.com/reasonmazebot</a><br/>
<br/>
<img src="/img" width=500 />
<img src="/img?1" width=500 />
<img src="/img?2" width=500 />
`)
  res.end();
})

app.get('/img', (req, res) => {
  const Canvas = require('canvas')
  const canvas = new Canvas(1000, 1000)
  const ctx = canvas.getContext('2d')

  randomMaze.run(ctx, [1000.0, 1000.0]);

  res.header('Content-type', 'image/png')
  res.send(canvas.toBuffer())
  res.end();
});

app.get('/post', (req, res) => {
  if (!hasBeenLongEnough()) {
    res.send('Not enough time elapsed')
    res.end()
    return
  }

  updateLastTime()
  const Canvas = require('canvas')
  const canvas = new Canvas(1000, 1000)
  const ctx = canvas.getContext('2d')

  const seed = randomMaze.run(ctx, [1000.0, 1000.0]);

  const data = canvas.toBuffer().toString('base64');
  postImage('maze: ' + (seed.toString(16)), data, err => {
    console.log('done')
    if (err) console.log('failed', err)
    res.send('Done')
    res.end();
  })
});

const postImage = (messageText, b64content, done) => {
  // first we must post the media to Twitter
  twit.post('media/upload', { media_data: b64content }, function (err, data, response) {
    if (err) return done(err)
    // now we can assign alt text to the media, for use by screen readers and
    // other text-based presentations and interpreters
    var mediaIdStr = data.media_id_string
    var altText = messageText
    var meta_params = { media_id: mediaIdStr, alt_text: { text: altText } }

    twit.post('media/metadata/create', meta_params, function (err, data, response) {
      if (err) return done(err)
      // now we can reference the media and post a tweet (media will attach to the tweet)
      var params = { status: messageText, media_ids: [mediaIdStr] }

      twit.post('statuses/update', params, function (err, data, response) {
        done(err)
      })
    })
  })
}

var listener = app.listen(process.env.PORT, function () {
  console.log('Your bot is running on port http://localhost:' + listener.address().port);
});

