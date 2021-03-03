let http = require('http');
let fs = require('fs');
let path = require('fs');
const crypto = require('mime-types');
const wellcrap = require('crypto');
const { connection } = require('websocket');
const { SSL_OP_SSLEAY_080_CLIENT_DH_BUG } = require('constants');

var room ={"users":[], "messages": [],"websockets":[]};

const hostname = '127.0.0.1';
const port = 8080;
var rooms= {room:[]}
let server = http.createServer(function(req, res)
{
    console.log(JSON.stringify(req.headers));
    if (req.headers["connection"]=="keep-alive"&&req.headers["cache-control"]=="max-age=0")
    {
console.log("WELP");
    res.writeHead(200, {
    'Content-Type': 'text/html'
    });
    fs.readFile('work.html', function(err, content){
    res.write(content);
    });
    console.log(`Server running at http://${hostname}:${port}/`);
    }else
    {
    console.log("WELP2");
        res.writeHead(200, {
        'Content-Type': 'text/html'
        });
        fs.readFile('Chat.html', function(lol, content2){
        res.write(content2);
        });

    }
    res.flushHeaders;
    
}).listen(port);
const WebSocketServer = require('websocket').server;
let ws = new WebSocketServer ({httpServer : server});

ws.on('request', function (request) 
{
    var connection = request.accept(null,request.origin);
    console.log("connection made");
    connection.on('message', function (mess) 
    {
            if (mess.type == "utf8" )
            {
                console.log("here");
                console.log("Received Message:"  + mess.utf8Data);
                var res = mess.utf8Data.split(" ");
                var start =res[0]
                

                for (i=1;i<res.length;i++)
                {
                    var rest=res[i];
                    
                }
                if (res[0]=="join")
                {
                    var roomName=res[2];
                    console.log("in the room adding stament");
                    rooms[roomName] = {"user":res[2],"websockets":[ws]} ;
                }
                else
                {

                    jsonMessage = {"user": res[0], "message": res}
                    for ( websockets of rooms[roomName]['websockets'])
                     {
                        websockets.send(JSON.stringify(jsonMessage));
                     } 
                }

                connection.sendUTF(mess.utf8Data);
            }
            else if (mess.type == "binary") 
            {
                console.log("here or here");
                console.log("Received Binary Message of"+ mess.binaryData.length + " bytes");
                connection.sendBytes(mess.binaryData);
            }
        });
        connection.on("close", function(reasonCode, description) {
            console.log((new Date()) + " Peer " + connection.remoteAddress + " disconnected.");
        });


});






















//     // var headers= JSON.stringify(request.headers)
//     // console.log(headers);
//     // var lol=JSON.parse(headers);
//     // if (lol.connection=="keep-alive")
//     // {
//     //     console.log("we got a message");
//     //     response.writeHead(200, {'Content-Type': 'text/html' });
//     //     fs.readFile('index.html', function(err, content){response.write(content);});

//     // }
//     // else if (lol.upgrade=="websocket")
//     // {
//     //     console.log("WE DID IT BOUS")
//     //     // Read the websocket key provided by the client: 
//     //     // const acceptKey = response.headers['sec-websocket-key']; 
//     //     // console.log(acceptKey);
//     //     // Generate the response value to use in the response: 
//     //     const hash = generateAcceptValue("XFfvtdMtEfiHLwyRv36tnQ=="); 
      
//     //     // Write the HTTP response into an array of response lines: 
//     //     const responseHeaders = [ 'HTTP/1.1 101 Switching Protocols', 'Upgrade: websocket', 'Connection: Upgrade', `Sec-WebSocket-Accept: ${hash}` ]; 
//     //     // Write the response back to the client socket, being sure to append two 
//     //     // additional newlines so that the browser recognises the end of the response 
//     //     // header and doesn't continue to wait for more header data: 
//     //     response.writeHead(101,{"Upgrade": 'websocket','Connection' : "Upgrade","`Sec-WebSocket-Accept" : '${hash}'})
//     //     console.log(responseHeaders.join('\r\n') );

//     //         response.on('data', buffer => 
//     //         {
//     //             const message = parseMessage(buffer);
//     //             if (message) 
//     //             {
//     //             // For our convenience, so we can see what the client sent
//     //             console.log(message);
//     //             // We'll just send a hardcoded message in this example 
//     //             response.write(constructReply({ message: 'Hello from the server!' })); 
//     //             } 
//     //             else if (message === null) 
//     //             { 
//     //                 console.log('WebSocket connection closed by the client.'); 
//     //             }
//     //           });
              

//     // }

   
// // });
// // server.on('keep-alive', function (req, socket) 
// // {
// //     onsole.log("we got a message");
// //     response.writeHead(200, {
// //     'Content-Type': 'text/html'
// //     });
// //     fs.readFile('index.html', function(err, content){
// //     response.write(content);
// //     });
// // });
// // server.on('Upgrade', function (req, socket) 
// // {
// //     if (lol.upgrade=="websocket")
// //     {
// //         console.log("WE DID IT BOUS")
// //         // Read the websocket key provided by the client: 
// //         const acceptKey = socket.headers['sec-websocket-key']; 
// //         console.log(acceptKey);
// //         // Generate the response value to use in the response: 
// //         const hash = generateAcceptValue(acceptKey); 

// //         // Write the HTTP response into an array of response lines: 
// //         const responseHeaders = [ 'HTTP/1.1 101 Switching Protocols', 'Upgrade: websocket', 'Connection: Upgrade', `Sec-WebSocket-Accept: ${hash}` ]; 
// //         // Write the response back to the client socket, being sure to append two 
// //         // additional newlines so that the browser recognises the end of the response 
// //         // header and doesn't continue to wait for more header data: 
// //         response.write(responseHeaders.join('\r\n'));
// //         console.log(responseHeaders.join('\r\n') );

// //             socket.on('data', buffer => 
// //             {
// //                 const message = parseMessage(buffer);
// //                 if (message) 
// //                 {
// //                 // For our convenience, so we can see what the client sent
// //                 console.log(message);
// //                 // We'll just send a hardcoded message in this example 
// //                 socket.write(constructReply({ message: 'Hello from the server!' })); 
// //                 } 
// //                 else if (message === null) 
// //                 { 
// //                     console.log('WebSocket connection closed by the client.'); 
// //                 }
// //               });
              

// //      }
// // });
// server.on('upgrade', function (req, socket) {
//     if (req.headers['upgrade'] !== 'websocket') {
//       socket.end('HTTP/1.1 400 Bad Request');
//       return;
//     }
//     // Read the websocket key provided by the client: 
//     const acceptKey = req.headers['sec-websocket-key']; 
//     // Generate the response value to use in the response: 
//     const hash = generateAcceptValue(acceptKey); 
//     // Write the HTTP response into an array of response lines: 
//     const responseHeaders = [ 'HTTP/1.1 101 Web Socket Protocol Handshake', 'Upgrade: WebSocket', 'Connection: Upgrade', `Sec-WebSocket-Accept: ${hash}` ]; 
//     // Write the response back to the client socket, being sure to append two 
//     // additional newlines so that the browser recognises the end of the response 
//     // header and doesn't continue to wait for more header data: 
//     socket.write(responseHeaders.join('\r\n') + '\r\n\r\n');
//   });

function readFile(req) {
    fs.readFile("src/textFiles/testFile.txt", function(err, buf) {
        if (buf) {
            console.log(buf.toString());
            return buf.toString();
        }
    });
}
function generateAcceptValue (acceptKey) 
{
    const crypto=require('crypto')
    return crypto.createHash('sha1').update(acceptKey + '258EAFA5-E914-47DA-95CA-C5AB0DC85B11', 'binary').digest('base64');
}
function constructReply(data)
{
// TODO: Construct a WebSocket frame Node.js socket buffer
}
function parseMessage(buffer) 
{
    const firstByte = buffer.readUInt8(0);
    const isFinalFrame = Boolean((firstByte >>> 7) & 0x1); 
    const [reserved1, reserved2, reserved3] = [ Boolean((firstByte >>> 6) & 0x1), Boolean((firstByte >>> 5) & 0x1), Boolean((firstByte >>> 4) & 0x1) ]; 
    const opCode = firstByte & 0xF; 
    // We can return null to signify that this is a connection termination frame 
    if (opCode === 0x8) 
    {
    return null; 
    }
    // We only care about text frames from this point onward 
    if (opCode !== 0x1) 
    {
    return; 
    }
    const secondByte = buffer.readUInt8(1); 
    const isMasked = Boolean((secondByte >>> 7) & 0x1); 
    // Keep track of our current position as we advance through the buffer 
    let currentOffset = 2; let payloadLength = secondByte & 0x7f; 
    if (payloadLength > 125) 
    { 
    if (payloadLength === 126) 
    { 
    payloadLength = buffer.readUInt16BE(currentOffset); 
    currentOffset += 2; 
    } 
    else 
    { 
    // 127 
    // If this has a value, the frame size is ridiculously huge! 
    const leftPart = buffer.readUInt32BE(currentOffset); 
    const rightPart = buffer.readUInt32BE(currentOffset += 4); 
    // Honestly, if the frame length requires 64 bits, you're probably doing it wrong. 
    // In Node.js you'll require the BigInt type, or a special library to handle this. 
    throw new Error('Large payloads not currently implemented'); 
        } 
        }
}