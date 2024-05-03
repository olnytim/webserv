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
    const value = document.cookie;
    const cookie_start = value.substring(value.indexOf('cookie'));
    console.log(cookie_start)
    console.log(cookie_start.split('=')[1].substring(0, cookie_start.split('=')[1].indexOf(';')))
    return cookie_start.split('=')[1].substring(0, cookie_start.split('=')[1].indexOf(';'))
}
changeCookieButton.addEventListener('click', function(event) {
    event.preventDefault();
    setCookie();
    setHeader(getCookie());
});

setHeader(getCookie());
