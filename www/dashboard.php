<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="stylesheet" href="css/bootstrap.min.css">
        <script src="js/bootstrap.min.js"></script>
    </head>
    <body>
        <nav class="navbar navbar-expand-lg navbar-dark bg-primary">
            <div class="container-fluid">
                <div class="navbar-brand">Best Buy Totaltech Inside Dashboard</div>
            </div>
        </nav>
        <div class="container">
            <div class="row mb-3">
                <div class="col-md-1 themed-grid-col"></div>
                <div class="col-md-10 themed-grid-col"></div>
                <div class="col-md-1 themed-grid-col"></div>
            </div>
            <div class="row mb-3">
                <div class="col-md-1 themed-grid-col"></div>
                <div class="col-md-10 themed-grid-col">
                    <div class="card border-primary mb-3">
                        <div class="card-body">
                            <h4 class="card-title">Customer Events</h4>
                            <table class="table table-hover">
                                <thead>
                                    <tr>
                                        <th>Customer ID</th>
                                        <th>Product ID</th>
                                        <th>Serial No.</th>
                                        <th>Temperature</th>
                                        <th>Created</th>
                                        <th></th>
                                        <th></th>
                                    </tr>
                                </thead>
                                </tbody>
                                    <?php
                                        $conn = new mysqli('127.0.0.1:3306', 'hackblue22', 'fuzzer', 'hackblue22');
                                        if($conn->connect_error ) {
                                            echo "E1";
                                            exit;
                                        }
                                        $sql = "SELECT customer_id, product_id, serial_no, temperature, created FROM events ORDER BY created DESC";
                                        $result = mysqli_query($conn, $sql);
                                        while($row = mysqli_fetch_array($result)) {
                                            echo "<tr>";
                                            echo "<td>" . $row['customer_id'] . "</td>";
                                            echo "<td>" . $row['product_id'] . "</td>";
                                            echo "<td>" . $row['serial_no'] . "</td>";
                                            echo "<td>" . $row['temperature'] . "</td>";
                                            echo "<td>" . $row['created'] . "</td>";
                                            echo "<td><button type='button' class='btn btn-success btn-sm'>Schedule</button></td>";
                                            echo "<td><button type='button' class='btn btn-danger btn-sm'>Resolve</button></td>";
                                            echo "</tr>";
                                        }
                                        $conn->close();
                                    ?>
                                </tbody>
                            </table>
                        </div>
                    </div>
                </div>
                <div class="col-md-1 themed-grid-col"></div>
            </div>
            <div class="row mb-3">
                <div class="col-md-3 themed-grid-col"></div>
                <div class="col-md-6 themed-grid-col text-center">
                    <img src="hackblue22.svg"/>
                </div>
                <div class="col-md-3 themed-grid-col"></div>
            </div>
            <div class="row mb-3">
                <div class="col-md-1 themed-grid-col"></div>
                <div class="col-md-10 themed-grid-col text-center">
                    <p class="text-primary">Manny Peterson's Hack Blue 22 Project (C)Copyright 2022 Best Buy Co., Inc. All Rights Reserved.</p>
                </div>
                <div class="col-md-1 themed-grid-col"></div>
            </div>
        </div>
    </body>
</html>