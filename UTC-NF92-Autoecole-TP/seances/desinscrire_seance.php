<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
  </head>

  <body>

    <?php
      // EXTRACTION DES VARIABLES

      $desinscriptions = $_POST["desinscriptions"];
      $deleteCount = 0;

      if (is_iterable($desinscriptions)) {
        
        // CONNEXION

        $dbhost = 'tuxa.sme.utc';
        $dbuser = 'nf92p065';
        $dbpass = 'uhJECSt3';
        $dbname = 'nf92p065';

        $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
        mysqli_set_charset($connect, 'utf8');

        foreach($desinscriptions as $d)
        {
          // EXTRACTION DES VARIABLES 

          $ids = explode("-", $d, 2); // split $d into ideleve, idseance
          $ideleve = $ids[0];
          $idseance = $ids[1];

          // TESTS DE CONFORMITE 

          $continue = true;

          if (empty($ideleve) || empty($idseance))
          {
            echo "<div class='alert'><p>&#10060</p><p>La requete n'est pas conforme. (données manquantes)<br>Elève ignoré.</p></div>";
            $continue = False;
          }
          elseif (!is_numeric($ideleve) || !is_numeric($idseance)) 
          {
            echo "<div class='alert'><p>&#10060</p><p>La requete n'est pas conforme. (données invalides)<br>Elève ignoré.</p></div>";
            $continue = False;
          }

          // DESINSCRIPTION DE L'ELEVE 
          
          if ($continue) {

            $query = "DELETE FROM inscription WHERE idseance = '$idseance' AND ideleve = '$ideleve'";
            $result = mysqli_query($connect, $query);
            if (!$result)
            {
              echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans desinscrire_seance.php section DESINSCRIPTION ELEVE<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
            }
            else {$deleteCount += 1;}
          }
        }

        echo "<div class='alert'><p>&#9989</p><p><br>$deleteCount désinscriptions ont été effectuées.</br></p></div>";

        // DECONNEXION

        mysqli_close($connect);
      }
      else {
        echo "<div class='alert'><p>&#10060</p><p>la liste des désinscriptions n'est pas itérable.</p></div>";
      }
    ?>

  </body>

</html>
