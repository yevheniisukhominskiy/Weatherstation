let switchMode = document.getElementById("switchMode");

switchMode.onclick = function () {
    let theme = document.getElementById("theme")

    if (theme.getAttribute("href") == "style/light-mode.css") {
        theme.href = "style/dark-mode.css";
        switchMode.src = "img/menu/theme-light.svg";
        
    } else {
        theme.href = "style/light-mode.css";
        switchMode.src = "img/menu/theme-dark.svg";
    }
}