const addedSession = document.getElementById('added_session');
const newSessionInput = document.getElementById('newSessionInput');
const changeSessionButton = document.getElementById('changeSessionButton');

changeSessionButton.addEventListener('click', function(event) {
    event.preventDefault();
    addedSession.innerText = newSessionInput.value;
    sessionStorage.setItem('session', newSessionInput.value);
});

addedSession.innerText = sessionStorage.getItem('session');


// setInterval(() => {
//     console.log(sessionStorage.getItem('session'));
// }, 1000);