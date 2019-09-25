#! /usr/bin/env elixir

skipcols = 0
showcols = 16

colmax = 32
rowmax = 7
fontw = 6
fonth = 8
IO.puts("P1")
IO.puts("# This is a pbm file")
IO.puts("#{colmax * fontw} #{rowmax * fonth}")

# "font.hex"
# |> File.read!()
IO.binread(:all)
|> String.split("\n")
|> Enum.flat_map(fn s -> String.split(s, ",") end)
|> Enum.reject(fn s -> s == "" end)
|> Enum.map(&String.trim/1)
|> Enum.map(fn "0x" <> hex ->
  hex
  |> String.to_integer(16)
  |> Integer.to_string(2)
  # |> String.replace("0", " ")
  # |> String.replace("1", "#")
  # |> String.pad_leading(8, " ")
  |> String.pad_leading(8, "0")
end)
|> Enum.chunk_every(colmax * fontw)
|> Enum.zip()
|> Enum.map(&Tuple.to_list/1)
|> Enum.map(&Enum.reverse/1)
|> Enum.map(&Enum.join/1)
|> Enum.map(&String.to_charlist/1)
|> Enum.map(&Enum.reverse/1)
|> Enum.zip()
|> Enum.map(&Tuple.to_list/1)
|> Enum.flat_map(&Enum.chunk_every(&1, 76))
|> Enum.each(&IO.puts/1)

## Extract glyphs
# |> Enum.chunk_every(fontw)
# |> Enum.drop(65)
# |> Enum.take(15)
# |> Enum.flat_map(fn glyph ->
#   glyph
#   |> Enum.map(&String.to_charlist/1)
#   |> Enum.map(&Enum.reverse/1)
#   |> Enum.zip()
#   |> Enum.map(&Tuple.to_list/1)
#   |> Enum.map(&to_string/1)
# end)
# |> Enum.each(&IO.puts/1)
