<html>

  <head>
    <meta charset="utf-8">
    <title></title>
  </head>
  <body>

      <?php

        echo "TRAVAUX : tests de conformite des donnees : (longueur du nom prenom;; par rapport aux longueurs limite varchar sur bdd)<br>";
        echo "pas forcement sur le formulaire, au moins toujours sur le serveur (securite) <br/>";
        echo "POPUP DE CONFIRMATION";

        date_default_timezone_set('Europe/Paris');
        $date = date("Y-m-d");
        $nom = $_POST["nomEleve"];
        $prenom = $_POST["prenomEleve"];
        $naissance = $_POST["dateEleve"];

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

        echo "<br> le nom saisi est : $nom";
        $query = "insert into eleves (nom, prenom, dateNaiss, dateInscription) values ('$nom', '$prenom', '$date', '$date')";

        echo "<br>$query<br>"; // important echo a faire systematiquement, c'est impose !

        $result = mysqli_query($connect, $query);
        // $query utilise comme parametre de mysqli_query
        // le test ci-dessous est desormais impose pour chaque appel de :
        // mysqli_query($connect, $query);
        if (!$result)
        {
        echo "<br>pas bon  ".mysqli_error($connect);
        }
        mysqli_close($connect);

      ?>

  </body>
</html>
