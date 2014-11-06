var PORT = 4242;
var HOST = '127.0.0.1';

var dgram = require("dgram");

var socket = dgram.createSocket("udp4");
var clients = {};

socket.on("error", function (err) {
  console.log("socket error:\n" + err.stack);
  socket.close();
});

socket.on("message", function (msg, rinfo) {
  
  if(!isClient(rinfo.address+":"+rinfo.port)){
	clients[rinfo.address+":"+rinfo.port] = {
		id : rinfo.address+":"+rinfo.port,
		address : rinfo.address, 
		port : rinfo.port, 
	}
	console.log(rinfo.address+":"+rinfo.port+" Added to clients")
  }
  
  broadcast(msg, rinfo.address+":"+rinfo.port)
  console.log("socket got: ", msg, " from " + rinfo.address + ":" + rinfo.port);
});

socket.on("listening", function () {
  var address = socket.address();
  console.log("socket listening " + address.address + ":" + address.port);
});

socket.bind(PORT, HOST);

function isClient(id)
{
	if(clients[id]) return true;
	return false
}

function broadcast(msg, exeption)
{
	console.log("broadcasting: ", msg, exeption);
	for(var key in clients){
		if(clients[key].id == exeption) continue;
		console.log("too: "+key);
		socket.send(msg, 0, msg.length, clients[key].port, clients[key].address, function(err, bytes) {
			if (err) throw err;
		});
	}
}

// Objects
var client = {
	id : "",
	address : "",
	port : "",
}