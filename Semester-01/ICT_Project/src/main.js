function login() {
    var username = document.getElementById('username').value;
    var password = document.getElementById('password').value;
    const x = ["Shaheer", "Farooq", "Yahya", "Guest"];
    const y = [123546, 654321, 789654, 59731];

    let i = 0;
    var link;
    while(i<4){
        if(username==x[i]&&password== parseInt(y[i])){
            alert('Username: ' + username + '\nPassword: ' + password+"\n Login Successful");
            link = document.createElement('a');
            switch(i){
                case 0:
                    link.href = "Home2.html"; break;
                case 1:
                    link.href = "Home3.html"; break;
                case 2:
                    link.href = "Home4.html"; break;
                default:
                link.href = "Login.html";
                alert("Wrong Password or Username entered");
            }
        
        window.open(link.href, '_blank');
        break;
    }
        else if(i==3 && (username!=x[i] || password!=y[i])){
            alert("You have entered the incorrect data");
        }
        i++;
    } 
}
  
function addingCard(){
    var Cardholder = document.getElementById('cardholder').value;
    var CardNumber = document.getElementById('cardnumber').value;
    var expdate = document.getElementById('expdate').value;
    var cvv = document.getElementById('cvv').value;

    alert("Success!\n\n" + "CardHolder: " + Cardholder + "\nCardNumber: " + CardNumber + "\nCard Expiration Date: " + expdate + "\nCVV: " + cvv);
}

function addingPass(){
    var Website = document.getElementById('websiteenter').value;
    var Username = document.getElementById('websiteusername').value;
    var Password = document.getElementById('websitepassword').value;

    alert("Success!\n\n" + "Website: " + Website + "\nUsername: " + Username + "\nPassword: " + Password);
}

function addingAddress(){
    var category = document.querySelector('input[name="address"]:checked').value;
    var fullname = document.getElementById('fname').value;
    var street = document.getElementById('street').value;
    var state = document.getElementById('state').value;
    var zip = document.getElementById('zip').value;
    var country = document.getElementById('country').value;

    alert("Success!\n\n" + category + "\nName: " + fullname + "\nStreet: " + street + "\nState: " + state + "\nZIP: " + zip + "\nCountry: " + country);
}



/*
function checkLogin(){
    var isLoggedIn = localStorage.getItem('isLoggedIn');
    isLoggedIn = false;
    if (isLoggedIn === 'true') {
        const Signin = document.querySelectorAll('.Signin'); // Get all login links
        Signin.forEach(link => {
            link.style.display = 'none'; // Hide login links if logged in
        });
  
        const AddRecord = document.querySelectorAll('.AddRecord'); // Get all add card links
        AddRecord.forEach(link => {
            link.setAttribute('href', 'AddRecord.html'); // Allow access to Add Card Details
        });
    } else {
        const Signin = document.querySelectorAll('.Signin'); // Get all login links
        Signin.forEach(link => {
            link.style.display = 'inline-block'; // Show login links if not logged in
        });
    
        const AddRecord = document.querySelectorAll('.AddRecord'); // Get all add card links
        AddRecord.forEach(link => {
            link.removeAttribute('href'); // Remove access to Add Card Details
            link.addEventListener('click', (e) => {
            e.preventDefault(); // Prevent default behavior of link click
            alert('Please login to access Add Card Details.');
            // window.location.href = 'login.html'; // Redirect to the login page
            });
        });
    }
}
  
// Call checkLogin when the page loads to check the initial login state
document.addEventListener('DOMContentLoaded', checkLogin);

*/