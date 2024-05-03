const newCookieInput = document.getElementById('newCookieInput');
const changeCookieButton = document.getElementById('changeCookieButton');

function setCookie() {
    const newName = newCookieInput.value;
    document.cookie = `cookie=${newName}`;
}

function setHeader(value) {
    const addedCookie = document.getElementById('added_cookie');
    addedCookie.innerText = value;
}

function getCookie() {
    return document.cookie.split('; ').reduce((acc, cookie) => {
        const [name, value] = cookie.split('=');
        acc[name] = value;
        return acc;
    }, {});
}

changeCookieButton.addEventListener('click', function(event) {
    event.preventDefault();
    setCookie();
    setHeader(getCookie().cookie);
});

setHeader(getCookie().cookie);
