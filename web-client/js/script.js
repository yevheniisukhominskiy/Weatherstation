// Function to update sensor data on the web page
function updateSensorData() 
{
    // Create an XMLHttpRequest object
    var xhttp = new XMLHttpRequest();

    // Define a function to be executed when the XMLHttpRequest state changes
    xhttp.onreadystatechange = function() 
    {
        // Check if the request is completed and the response is successful (status 200)
        if (this.readyState == 4 && this.status == 200) {
            // Parse the received JSON data into a JavaScript object
            var data = JSON.parse(this.responseText);

            // Update the content of HTML elements on the web page with the received sensor data
            document.getElementById("temperature").innerText = data.temperature;
            document.getElementById("humidity").innerText = data.humidity;
            document.getElementById("pressure").innerText = data.pressure;
            document.getElementById("height").innerText = data.height;
        }
    };

    // Configure the XMLHttpRequest to make a GET request to "/sensor-data" on the server
    xhttp.open("GET", "/sensor-data", true);

    // Send the GET request
    xhttp.send();
}

// Call the updateSensorData() function every 5 seconds (5000 milliseconds)
setInterval(updateSensorData, 5000);