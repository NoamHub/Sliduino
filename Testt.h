"<!DOCTYPE HTML>\n"
"<html>\n"
	"<head>\n"
		"<style>\n"
		"a.button {\n"
			"-webkit-appearance: button;\n"
			"-moz-appearance: button;\n"
			"appearance: button;\n"
			"line-height:175%;\n"
			"text-align:center;\n"
			"text-decoration: none;\n"
			"font-size: 50px;\n"
			"color: initial;\n"
			"margin: 0 5%;\n"
			"padding: 0 2%;\n"
		"}\n"

		"input{\n"
			"width: 6%;\n"
			"font-size:45px;\n"
		"}\n"

		"h1{   \n"
		  "font-size:60px;\n"
		  "margin-bottom: 10px;\n"
		"}  \n"

		"h2{\n"
			"font-size:45px;\n"
			 "margin: 2% 0%;\n"
			 "display: inline-block;\n"
		"}\n"
		
		".left_header {\n"
			 "padding: 0 64px 0 5%;\n"
		"}\n"

		"hr{\n"
			"margin:5% 0;\n"
		"}\n"
		
		".direction_inputs{\n"
			"font-size: 47px;\n"
			"font-weight: bold;\n"
		"}\n"
		"</style>\n"
	"</head>\n"
	"<body>\n"

		"<h1> Direction </h1>\n"

		"<form method=\"GET\" action=\"/Start\" id=\"main_form\">\n"
			"<div class=\"direction_inputs\">\n"
				"<label>\n"
					"<input type=\"radio\" name=\"direction\" value=\"0\" checked /> To Motor\n"
				"</label>\n"

				"<label>\n"
					"<input type=\"radio\" name=\"direction\" value=\"1\" /> To !Motor\n"
				"</label>\n"
			"</div>\n"

			"<!-- Mid section -->\n"
			"<hr size=\"10%\" noshade color = \"brown\" > \n"

			"<h1> Operation </h1>\n"

			"<h2 class=\"left_header\"> Delay: </h2>\n"
			"<h2 style = \"padding: 0 0 0 30px; \"> [hh:] </h2>\n"
			"<input type = \"text\" name = \"DelayHours\" value = \"00\"/>\n"
			
			"<h2 style = \"padding: 0 0 0 3%; \"> [mm:] </h2>\n"
			"<input type = \"text\" name = \"DelayMinutes\" value = \"00\"/>\n"
			
			"<h2 style = \"padding: 0 0 0 3%; \"> [ss:] </h2>\n"
			"<input type = \"text\" name = \"DelaySeconds\" value = \"00\"/>\n"
		
			"<br/>\n"
			"<br/>\n"
			
			"<h2 style = \"padding: 0 10px 0 5%;\"> Run Time: </h2>\n"
			"<h2 style = \"\"> [hh:] </h2>\n"
			"<input type = \"text\" name = \"RunTimeHours\" value = \"00\"/>\n"
			
			"<h2 style = \"padding: 0 0 0 3%; \"> [mm:] </h2>\n"
			"<input type = \"text\" name = \"RunTimeMinutes\" value = \"00\"/>\n"
			
			"<h2 style = \"padding: 0 0 0 3%; \"> [ss:] </h2>\n"
			"<input type = \"text\" name = \"RunTimeSeconds\" value = \"00\"/>\n"
		"</form>\n"
		"<br/>\n"
		"<br/>\n"

		"<a href=\"#\" onclick=\"document.getElementById('main_form').submit()\" class=\"button\" \n"
		"style=\"background-color:green; margin: 0 2% 0 5%; \"> Start </a>\n"

		"<a href=\"/Stop\" class=\"button\" \n"
		"style=\"background-color:red;  margin: 0 2%  \"> Stop </a>\n"

		"<a href=\"/Reset\" class=\"button\" \n"
		"style=\"background-color:powderblue; float:right; margin: 0 5% 0 0;\"> Reset </a>\n"


		"<!-- Bottom section -->\n"
		"<hr size=\"10%\" noshade color = \"brown\"> \n"

		"<h1> Information </h1>\n"

		"<h2 class=\"left_header\"> Time to start: [hh:mm:ss] </h2>\n"

		"<h2 class=\"left_header\"> Running: [hh:mm:ss] </h2>\n"

		"<h2 class=\"left_header\"> End Time: [hh:mm:ss] </h2>\n"

		"<h2 class=\"left_header\"> #Steps: <span id=\"steps\">####</span></h2>\n"

				
		"<script>\n"
			"function pollSteps(){\n"
				"var x = new (this.XMLHttpRequest || ActiveXObject)('MSXML2.XMLHTTP.3.0');\n"
				"var url = '/?pollSteps';\n"
				"x.open('GET', url);\n"
				
				"x.onreadystatechange = function() {\n"
					"if(x.readyState === 4){\n"
						"document.getElementById('steps').innerHTML = x.responseText;\n"
					"}\n"
				"}\n"
				"x.send();\n"
			"}\n"
			
			"//setInterval(pollSteps, 5000);\n"
			"//pollSteps();\n"
		"</script>\n"
	"</body>\n"
"</html>\n"