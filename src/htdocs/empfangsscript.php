?php
//PHP Skript für das Extrahieren der Daten aus dem HTTP-Request und Speichern in eine Datenbank
// Logindaten für die Datenbankverbindung bereitstellen
$servername = "localhost";
$username = "########"; // dein User - Standard root
$password = "#######";  // dein Passwort - Standard keins vergeben
$dbname = "sensordaten"; // dein Datenbankname

// Verbindung zur Datenbank herstellen
$conn = new mysqli($servername, $username, $password, $dbname);
// Verbindung überprüfen
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
// Daten aus dem POST-Request auslesen
$temperature = $_POST['temperature'];
$humidity = $_POST['humidity'];
// SQL-Abfrage zum Einfügen der Daten vorbereiten
$sql = $conn->prepare("INSERT INTO sht31_daten (temperature, humidity) VALUES (?, ?)");
$sql->bind_param("ss", $temperature, $humidity); // "ss" bedeutet, dass zwei String-Werte gebunden werden
// Prüfen ob die Daten in die Datenbank geschrieben wurden
if ($sql->execute()) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql->error;
}
// Datenbankverbindung wieder schließen
$sql->close();
$conn->close();
?>