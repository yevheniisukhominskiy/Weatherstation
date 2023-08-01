// Function for predicting weather based on temperature, pressure, and humidity
function predictWeather(temperature, pressure, humidity) {
    if (temperature < 0) {
        return {
            text: "Сьогодні холодно. Одягайтеся тепліше!",
            icon: "cold"
        };
    } else if (temperature < 0 && humidity >= 70) {
        return {
            text: "Сьогодні холодно. Можливі опади в виді снігу.",
            icon: "snow"
        };
    } else if (temperature >= 30) {
        return {
            text: "Сьогодні спекотно. Запасіться водою!",
            icon: "hot"
        };
    } else if (temperature > 0 && temperature < 30) {
        return {
            text: "Сьогодні сонячно. День має бути гарним.",
            icon: "sun"
        };
    } else if (humidity >= 60 && pressure <= 750) {
        return {
            text: "Сьогодні пасмурно. Можливі опади у вигляді дощу.",
            icon: "rain"
        };
    } else {
        return {
            text: "Погода невизначена. Подивіться в вікно!",
            icon: "error"
        };
    }
}   

// Function to update sensor data on the web page
function updateSensorData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            var data = JSON.parse(this.responseText);

            // Update elements with actual sensor data
            document.getElementById("temperature").innerText = data.temperature;
            document.getElementById("humidity").innerText = data.humidity;
            document.getElementById("pressure").innerText = data.pressure;
            document.getElementById("height").innerText = data.height;

            // Predict the weather
            var weatherPrediction = predictWeather(data.temperature, data.pressure, data.humidity);

            // Update the element with the weather prediction text
            document.getElementById("weatherPrediction").innerText = weatherPrediction.text;

            // Set the weather icon
            var weatherIcon = document.getElementById("weatherIcon");
            weatherIcon.src = weatherPrediction.icon + ".svg";
        }
    };

    xhttp.open("GET", "/sensor-data", true);
    xhttp.send();
}

// Call the updateSensorData() function every 20 seconds
setInterval(updateSensorData, 5000);