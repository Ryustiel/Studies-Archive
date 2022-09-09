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
      mysqli_set_charset($connect, 'utf8');
      
      // RECUPERATION DES THEMES

      $query = "SELECT * FROM themes WHERE supprime=0";
      $result = mysqli_query($connect, $query);
      if (!$result) {
        echo "<div class='alert'><p>&#10060</p><p>Erreur SQL dans suppression_theme.php section RECUPERATION<br>".mysqli_error($connect)."<br>Query : $query</p></div>";
      }

      $options = "";
      while ($dtheme = mysqli_fetch_array($result, MYSQLI_NUM)) {
        $options .= "<option value=$dtheme[0]> $dtheme[1] </option>";
      }

      // CREATION DU FORMULAIRE

      echo "<div class='content'> <div class='header'><p>Supprimer un thème</p></div>";
      echo "<FORM METHOD='POST' ACTION='supprimer_theme.php' > <div class='container'>";
      echo "<div> <label>Selectionner un ou plusieurs Themes</label> <select name='idthemes[]' multiple size=10 required>";
      echo "$options";
      echo '</select></div>';
      echo '<p>Supprimer aussi les séances associées à venir ?</p>';
      echo '<input type="checkbox" id="deleteSeances" name="deleteSeances" value="true">';
      echo "<input type='submit' value='Supprimer les Themes Sélectionnés'>";
      echo '</div></form></div>';
      
      // DECONNEXION

      mysqli_close($connect);
    ?>

  </body>

</html>
