var io = require('socket.io').listen(8000);

io.sockets.on('connection', function (socket) {
  console.log('user connected');

  socket.on('action', function (data) {
    console.log('here we are in action event and data is: ' + data);
  });

  socket.on('message', function(msgtype, data, error){
          console.log('Got an new message:::::' + msgtype + ":" + data + ":" + error);
          });

socket.on('message', function(message, callback) {
    console.log(message);
    console.log(callback);
});


  setTimeout(function(){
    socket.send('hello');
  }, 3000);
});


var cc = io.of('/test')
.on('connection', function(socket){
    socket.emit('event_form_test', { name : 'socket.io test'});
});

