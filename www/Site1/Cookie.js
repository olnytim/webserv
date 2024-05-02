const newNameInput = document.getElementById('newNameInput');
const changeCookieButton = document.getElementById('changeCookieButton');

changeCookieButton.addEventListener('click', function(event) {
    event.preventDefault(); // Prevent the default behavior of the link

    // Get the value from the input field
    const newName = newNameInput.value;

    // Set the cookie with the new value
    document.cookie = `cookie=${newName}`;
    console.log(`cookie=${newName}`);
});