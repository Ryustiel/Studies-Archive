<html>

  <head>
    <meta charset="utf-8">
    <title></title>
    <link href="../styles/common.css" rel="stylesheet" type="text/css" />
    <link href="../styles/formulaires.css" rel="stylesheet" type="text/css" />
  </head>

  <body>

    <?php
      // CONNEXION

      $dbhost = 'tuxa.sme.utc';
      $dbuser = 'nf92p065';
      $dbpass = 'uhJECSt3';
      $dbname = 'nf92p065';

      $connect = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die ('Error connecting to mysql');
      mysqli_set_charset($connect, 'utf8'); //les données envoyées vers mysql sont encodées en UTF-8

      // RECUPERATION DONNEES ELEVES
      
      $query = "SELECT ideleve, nom, prenom FROM eleves ORDER BY nom";
      $result = mysqli_query($connect, $query);
      if (!$result)
      {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans consultation_eleve.php section RECUPERATION DONNEES ELEVES<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
      }

      // GENERATION DU FORMULAIRE

      echo "<div class='content'> <div class='header'><p>Consulter les informations d'un élève</p></div>";
      echo "<FORM METHOD='POST' ACTION='consulter_eleve.php'> <div class='container'>";
      echo "<div> <label>Selectionner un Eleve</label> <select name='ideleve' size='5'>";
      while ($deleve = mysqli_fetch_array($result, MYSQLI_NUM)) 
      {
        echo "<option value=$deleve[0]> $deleve[1] $deleve[2] </option>";
      }
      echo '</select></div>';
      echo "<input type='submit' value='Consulter l"."'élève"."'>";
      echo '</div></form></div>';

      // DECONNEXION

      mysqli_close($connect);
    ?>

  </body>

</html>
