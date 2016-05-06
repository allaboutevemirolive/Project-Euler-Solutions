let sum  = [1..999] |> List.filter (fun i -> i % 3 = 0 || i % 5 = 0) |> List.sum
