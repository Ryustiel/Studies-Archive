<html>

  <head>
    <meta charset="utf-8">
    <title>Thème Ajouté</title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
 
  </head>

  <body>
    <?php
        // EXTRACTION DES VARIABLES 

        $nom = $_POST["nomTheme"];
        $descriptif = $_POST["descriptifTheme"];
        $action = $_POST["action"]; // reactiver / remplacer

        // TESTS DE CONFORMITE 

        $continue = True;

        if (empty($nom) || empty($descriptif))
        {
            echo "<div class='alert'><p>&#10060</p><p>Toutes les valeurs doivent etre remplies. Le thème n'a pas été ajouté.</p></div>";
            $continue = False;
        }
        elseif ($nom != strip_tags($nom) || $descriptif != strip_tags($descriptif)) 
        {
            "<div class='alert'><p>&#10060</p><p>Des éléments html ont été détectés dans les informations du thème. e thème n'a pas pu être ajouté.</p></div>";
            $continue = False;
        }

        // $action n'a pas besoin d'etre verifee car elle n'est interpretee que comme un booleen (deux valeurs definies)
        
        if ($continue) {

            // CONNEXION

            $dbhost = 'tuxa.sme.utc';
            $dbuser = 'nf92p065';
            $dbpass = 'uhJECSt3';
            $dbname = 'nf92p065';

            $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
            mysqli_set_charset($connect, 'utf8');

            // nettoyage des donnees
            $nom = mysqli_real_escape_string($connect, $nom);
            $descriptif = mysqli_real_escape_string($connect, $descriptif);

            if ($action == 'reactiver')
            {
                // REACTIVER LE THEME

                $query = "UPDATE themes SET supprime = 0 WHERE nom = '$nom'"; // query outside of the function call
                $result = mysqli_query($connect, $query);
                if (!$result)
                {
                echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans valider_theme.php section REACTIVER THEME<br>".mysqli_error($connect)."<br>Query : $query</p></div>"; // add the query at the end of the error message
                }
                else
                {
                  echo "<div class='alert'><p>&#9989</p><p>Le thème a été réactivé</p></div>";
                }
            }
            else
            {
                // METTRE A JOUR LE DESCRIPTIF

              $query = "UPDATE themes SET supprime = 0, descriptif = '$descriptif' WHERE nom = '$nom'"; // query outside of the function call

              $result = mysqli_query($connect, $query);
              if (!$result) {
              echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans valider_theme.php section MAJ DESCRIPTIF<br>".mysqli_error($connect)."<br>Query : $query</p></div>"; // add the query at the end of the error message
              }
              else {
              echo "<div class='alert'><p>&#9989</p><p>Le thème $nom a été remplacé</p></div>";
              }
            }
            // DECONNEXION

            mysqli_close($connect);
        }
    ?>
  </body>

</html>
