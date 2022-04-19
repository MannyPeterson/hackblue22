<?php


$conn = new mysqli('127.0.0.1:3306', 'hackblue22', 'fuzzer', 'hackblue22');
if($conn->connect_error ) {
	echo "E1";
	exit;
}


$sql = "SELECT customer_id, product_id, serial_no, temperature, created FROM events";


$result = mysqli_query($conn, $sql);

?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="css/bootstrap.min.css">
    <script src="js/bootstrap.min.js"></script>
</head>
<body>
<div class="container">
<div class="card border-primary mb-3">
  <div class="card-body">
  <h4 class="card-title">BIjaliwejfalejflaisejflaisfej</h4>
  <p class="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
</div>
</div>
<div class="card border-primary mb-3">
  <div class="card-body">
  <h4 class="card-title">Best Buy Totaltech Inside Events</h4>
    <table class="table table-hover">
        <thead>
            <tr>
                <th>Customer ID</th>
                <th>Product ID</th>
                <th>Serial No.</th>
                <th>Temperature</th>
                <th>Created</th>
            </tr>
        </thead>
    <tbody>
<?php

while($row = mysqli_fetch_array($result)) {
    echo "<tr><td>" . $row['customer_id'] . "</td>";
    echo "<td>" . $row['product_id'] . "</td>";
    echo "<td>" . $row['serial_no'] . "</td>";
    echo "<td>" . $row['temperature'] . "</td>";
    echo "<td>" . $row['created'] . "</td></tr>";
}

?>
  </div>
</div>
</div>
</body>
</html>

<?php

$conn->close();