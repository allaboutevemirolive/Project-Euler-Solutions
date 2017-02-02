class Coordinate
  attr_accessor :x, :y
  def initialize(x, y)
    @x = x
    @y = y
  end
end

class Square
  attr_accessor :rad, :len, :midx, :midy

  def initialize(rad, len, midx, midy)
    @rad = rad
    @len = len
    @midx = midx
    @midy = midy
  end

  def leftdown
    Coordinate.new(Math.sqrt(0.5) * @len * Math.cos(@rad +5 * Math::PI / 4) +
                       @midx, Math.sqrt(0.5) * @len * Math.sin(@rad + 5 * Math::PI / 4) + @midy)
  end

  def leftup
    Coordinate.new(Math.sqrt(0.5) * @len * Math.cos(@rad + 3 * Math::PI / 4) +
                       @midx, Math.sqrt(0.5) * @len * Math.sin(@rad + 3 * Math::PI / 4) + @midy)
  end

  def rightdown
    Coordinate.new(Math.sqrt(0.5) * @len * Math.cos(@rad + 7 * Math::PI / 4) +
                       @midx, Math.sqrt(0.5) * @len * Math.sin(@rad + 7 * Math::PI / 4) + @midy)
  end

  def rightup
    Coordinate.new(Math.sqrt(0.5) * @len * Math.cos(@rad + Math::PI / 4) +
                       @midx, Math.sqrt(0.5) * @len * Math.sin(@rad + Math::PI / 4) + @midy)
  end

  def eliminate(maxdis, minx, miny, maxx, maxy)
    mdsq = maxdis * @len
    minxfail=((@midx-minx).abs > mdsq)
    maxxfail=((@midx-maxx).abs > mdsq)
    minyfail=((@midy-miny).abs > mdsq)
    maxyfail=((@midy-maxy).abs > mdsq)

    return minxfail && maxxfail && minyfail && maxyfail
  end
end

cor = [Square.new(0, 1, 0, 0)]
miny = -0.5
maxy = 0.5
minx = -0.5
maxx = 0.5
s1 = Math.atan2(3, 4)

while cor.length < 1000
  newcor = []
  cor.each do |sq|
    ncrad = sq.rad + s1
    nclen = sq.len * 0.8
    mdx = sq.leftup.x + Math.sqrt(0.5) * nclen * Math.cos(ncrad + Math::PI / 4)
    mdy = sq.leftup.y + Math.sqrt(0.5) * nclen * Math.cos(ncrad + Math::PI / 4)

    nsq = Square.new(ncrad - Math::PI / 2, nclen, mdx, mdy)

    unless nsq.eliminate(5, minx, miny, maxx, maxy)
      newcor << nsq
      minx = mdx if mdx < minx
      maxx = mdx if mdx > maxx
      miny = mdy if mdy < miny
      maxy = mdy if mdy > maxy
    end
  end
  cor = newcor
end

puts ((maxx - minx) * (maxy - miny)).round(10)