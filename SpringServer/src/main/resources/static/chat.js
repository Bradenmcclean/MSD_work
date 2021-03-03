let ws = new WebSocket("ws://localhost:8080/index")
let name = "";

function getChat ()
{
	let chatmessage = document.getElementById("chatmessage").value
	ws.addEventListener("message", function(event) 
	{
		console.log("messageFromServer", event.data)
    })
	ws.send(name +" "+ chatmessage)
	
    ws.onmessage = function(event) 
{
   
      //create a JSON object
      var jsonObject = JSON.parse(event.data);
      var username = jsonObject.User;
      var message = jsonObject.Message;
		
      console.log('message recived')

	 let chat= document.createElement('chat')
	 chat.innerHTML = "<br>"+username+": "+ message
	  document.body.appendChild(chat)
   
}
}

function getRoom () 
{
	lol=new XMLHttpRequest()
	let room = document.getElementById("ChatRoom").value
	name=document.getElementById("username").value
	ws.addEventListener("message", function(event) 
	{
		console.log("messageFromServer", event.data)
	})
	ws.send(room+" "+ name)
	//add the listener before the send
	
	
	lol.open('GET', 'Chat.html', true);
	lol.onload=function ()
	{
	document.body.innerHTML=lol.response
	}
	
	lol.send();
	//put the on load before the send 
	
}