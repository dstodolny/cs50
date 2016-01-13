<div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
                <th>TOTAL</th>
            </tr>
        </thead>
        <tbody>
            <?php

                foreach ($positions as $position)
                {
                    print("<tr>");
                    print("<td>{$position["symbol"]}</td>");
                    print("<td>{$position["name"]}</td>");
                    print("<td>{$position["shares"]}</td>");
                    print("<td>{$position["price"]}</td>");
                    print("<td>{$position["value"]}</td>");
                    print("</tr>");
                }

            ?>
            <tr>
                <td>CASH</td>
                <td></td>
                <td></td>
                <td></td>
                <td><?= $cash ?></td>
            </tr>
        </tbody>
        <tfoot>
            <tr>
                <td></td>
                <td></td>
                <td></td>
                <td></td>
                <td><?= $total ?></td>
            </tr>
        </tfoot>
    </table>
</div>
