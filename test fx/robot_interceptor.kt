import java.util.*
import java.io.*

class FastReader(`in`: InputStream) {
    private val reader: BufferedReader = BufferedReader(InputStreamReader(`in`))
    private var tokenizer: StringTokenizer? = null

    operator fun next(): String? {
        while (tokenizer == null || !tokenizer!!.hasMoreElements()) {
            val line = reader.readLine() ?: return null
            tokenizer = StringTokenizer(line)
        }
        return tokenizer!!.nextToken()
    }

    fun nextLong(): Long = next()!!.toLong()
}

fun countDiskPoints(n: Long, m: Long, r: Long): Long {
    var count = 0L
    for (y in 0L..Math.min(r, m)) {
        val rs = r * r
        val ys = y * y
        val dx = Math.floor(Math.sqrt((rs - ys).toDouble())).toLong()
        count += Math.min(n, dx) + 1
    }
    return count
}

fun countOverlapPoints(n: Long, m: Long, r: Long): Long {
    var count = 0L
    val rs = r * r
    for (y in 0L..m) {
        val dyStart = y * y
        val dyEnd = (m - y) * (m - y)
        if (dyStart > rs || dyEnd > rs) continue
        
        val dxStartMax = Math.floor(Math.sqrt((rs - dyStart).toDouble())).toLong()
        val dxEndMax = Math.floor(Math.sqrt((rs - dyEnd).toDouble())).toLong()
        
        // Disk start: [0, dxStartMax]
        // Disk end: [n - dxEndMax, n]
        val xMin = Math.max(0L, n - dxEndMax)
        val xMax = Math.min(n, dxStartMax)
        
        if (xMin <= xMax) {
            count += (xMax - xMin + 1)
        }
    }
    return count
}

fun solve() {
    val fr = FastReader(System.`in`)
    val out = PrintWriter(System.out)
    
    val nextT = fr.next() ?: return
    val t = nextT.toInt()
    
    repeat(t) {
        var n = fr.nextLong()
        var m = fr.nextLong()
        val r = fr.nextLong()
        
        if (m > n) {
            val temp = n
            n = m
            m = temp
        }
        
        // Total points in grid: (n+1)*(m+1)
        // Blocking condition: (dist(TL) <= r) AND (dist(BR) <= r)
        // Non-blocking region: dist(TL) > r OR dist(BR) > r
        // TL boundary: x=0 or y=m
        // BR boundary: y=0 or x=n
        // dist(TL) = min(x, m-y)
        // dist(BR) = min(y, n-x)
        
        // Candidate area S_cand = N - (|A| + |B| - |A \cap B|)
        // A = {(x,y) : x > r and y < m-r} (dist to TL > r)
        // B = {(x,y) : y > r and x < n-r} (dist to BR > r)
        
        val totalPoints = (n + 1) * (m + 1)
        val areaA = Math.max(0L, n - r) * Math.max(0L, m - r)
        val areaB = Math.max(0L, n - r) * Math.max(0L, m - r)
        val intersectionArea = Math.max(0L, n - 2 * r - 1) * Math.max(0L, m - 2 * r - 1)
        
        val sCand = totalPoints - (areaA + areaB - intersectionArea)
        
        // Disqualify disk points at (0,0) and (n,m)
        val diskStart = countDiskPoints(n, m, r)
        val diskEnd = diskStart // Symmetric
        val diskOverlap = countOverlapPoints(n, m, r)
        
        val ans = sCand - diskStart - diskEnd + diskOverlap
        out.println(Math.max(0L, ans))
    }
    out.flush()
}

fun main() {
    solve()
}
