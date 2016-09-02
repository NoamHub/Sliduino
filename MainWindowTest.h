
HTTP/1.1 200 OK
Content-Type: text/html
<!DOCTYPE HTML>
<html>
<head>
<style>
a.button {-webkit-appearance: button;
-moz-appearance: button;
appearance: button;
line-height:175%;
text-align:center;
text-decoration: none; 
font-size: 50px;  
color: initial;  
margin: 0 5%;
padding: 0 2%;  
}  

input{   
  width: 10%;   
  font-size:30px;   
}  

h1{   
  width:10%;
  font-size:40;   
}  

h2{   
  width:10%;
  font-size:30px;   
}  

hr{   
  margin:5% 0; 
}  

}  

</style>
</head>
<body> 

<h1> Directin <h1/>   

<a href=\"/?ToMotor\" class=\"button\" 
   style=\"background-color:powderblue; \">To Motor </a> 
  
<a href=\"/?ToNotMotor\" class=\"button\" 
   style=\"background-color:powderblue; float: right;\">To !Motor </a>

<! Mid section > 
<hr size=\"10%\" noshade color = \"brown\">

<h1> Operation </h1>

<h2 style = \"display:inline; padding: 0 64px 0 5%;\"> Delay: </h2>
<h2 style = \"display:inline; \"> [hh:] </h2> 
<input type = \"text\" name = \"DelayHours\" value = \"00\"/> 
<h2 style = \"display:inline; padding: 0 0 0 5%; \"> [mm:] </h2>
<input type = \"text\" name = \"DelayMinutes\" value = \"00\"/>  
<h2 style = \"display:inline; padding: 0 0 0 5%; \"> [ss:] </h2>  
<input type = \"text\" name = \"DelaySeconds\" value = \"00\"/> 
<br/>
<br/>
<h2 style = \"display:inline; padding: 0 10px 0 5%;\"> Run Time: </h2>   
<h2 style = \"display:inline; \"> [hh:] </h2> 
<input type = \"text\" name = \"RunTimeHours\" value = \"00\"/>
<h2 style = \"display:inline; padding: 0 0 0 5%; \"> [mm:] </h2>
<input type = \"text\" name = \"RunTimeMinutes\" value = \"00\"/>  
<h2 style = \"display:inline; padding: 0 0 0 5%; \"> [ss:] </h2>  
<input type = \"text\" name = \"RunTimeSeconds\" value = \"00\"/> 

<br/>
<br/>
<br/>
<br/>

<a href=\"/?Start\" class=\"button\"  
style=\"background-color:green; margin: 0 2% 0 5%; \"> Start </a> 

<a href=\"/?Pause\" class=\"button\"
style=\"background-color:orange; margin: 0 2% \"> Pause </a>   

<a href=\"/?Stop\" class=\"button\"  
style=\"background-color:red;  margin: 0 2%  \"> Stop </a>

<a href=\"/?Reset\" class=\"button\" 
style=\"background-color:powderblue; float:right; margin: 0 5% 0 0;\"> Reset </a>


<! Bottom section >
<hr size=\"10%\" noshade color = \"brown\">

<h1> Information </h1> 

</body>
</html>









