<?php

$file = fopen("input.txt", "r");

function mapNumbers($number)
{
    return intval(trim($number));
}

// extract numbers to draw
$line = fgets($file);
$numberstodraw = array_map("mapNumbers", explode(",", $line));

$boards = array();
$row = 0;

// load all boards
while (($line = fgets($file)) !== false)
{
    if (trim($line) == "")
    {
        // line is empty, a new board must be starting
        array_push($boards, ["numbers" => []]);
        $row = 0;

        continue;
    }

    $numbers = array_map("mapNumbers", preg_split("/ +/", trim($line)));

    for ($i = 0; $i < count($numbers); $i++)
    {
        array_push($boards[count($boards) - 1]["numbers"], ["number" => $numbers[$i], "x" => $i, "y" => $row]);
    }

    $row++;
}

fclose($file);

$winner = null;
$lastwinner = null;
$last;
$just;

// its a 3 scope deep loop!
foreach ($numberstodraw as $drawn)
{
    foreach ($boards as &$board)
    {
        foreach ($board["numbers"] as &$number)
        {
            if ($number["number"] == $drawn)
            {
                $number["drawn"] = true;
            }
        }

        // do we have a winner?!

        // also more holy wtf loops
        for ($i = 0; $i < 5; $i++)
        {
            $elems = array_filter($board["numbers"], function($number)
            {
                global $i;
                return $number["x"] == $i && isset($number["drawn"]);
            });

            if (count($elems) == 5)
            {
                if (!isset($winner))
                {
                    $winner = $board;
                    $just = $drawn;
                }

                if (!isset($board["won"]))
                {
                    $lastwinner = $board;
                    $last = $drawn;

                    $board["won"] = true;
                }
            }
        }

        for ($i = 0; $i < 5; $i++)
        {
            $elems = array_filter($board["numbers"], function($number)
            {
                global $i;
                return $number["y"] == $i && isset($number["drawn"]);
            });

            if (count($elems) == 5)
            {
                if (!isset($winner))
                {
                    $winner = $board;
                    $just = $drawn;
                }

                if (!isset($board["won"]))
                {
                    $lastwinner = $board;
                    $last = $drawn;

                    $board["won"] = true;
                }
            }
        }
    }
}

function getScore($board, $last)
{
    // holy map filter funcs
    $unmarked = array_filter($board["numbers"], function($number)
    {
        return !isset($number["drawn"]);
    });

    $unmarked = array_map(function($number)
    {
        return $number["number"];
    }, $unmarked);

    return array_sum($unmarked) * $last;
}

echo "part one: " . getScore($winner, $just) . "\n";
echo "part two: " . getScore($lastwinner, $last) . "\n";