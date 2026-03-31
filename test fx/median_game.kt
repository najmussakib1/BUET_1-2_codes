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

    fun nextInt(): Int = next()!!.toInt()
    fun nextLong(): Long = next()!!.toLong()
}

fun solve() {
    val fr = FastReader(System.`in`)
    val out = PrintWriter(System.out)
    
    val tStr = fr.next() ?: return
    val t = tStr.toInt()
    
    repeat(t) {
        val n = fr.nextInt()
        val m = fr.nextInt()
        
        val a = LongArray(n) { fr.nextLong() }
        val b = LongArray(m) { fr.nextLong() }
        
        // Reachable range for a
        val startA = if (n == 1) 0 else 1
        val endA = if (n == 1) 0 else n - 2
        
        // Reachable range for b
        val startB = if (m == 1) 0 else 1
        val endB = if (m == 1) 0 else m - 2
        
        // Check intersection of a[startA..endA] and b[startB..endB]
        var i = startA
        var j = startB
        var found = false
        
        while (i <= endA && j <= endB) {
            if (a[i] == b[j]) {
                found = true
                break
            } else if (a[i] < b[j]) {
                i++
            } else {
                j++
            }
        }
        
        if (found) out.println("YES") else out.println("NO")
    }
    out.flush()
}

fun main() {
    solve()
}
