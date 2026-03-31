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
}

fun power(a: Long, b: Long, m: Long): Long {
    var res = 1L
    var base = a % m
    var exp = b
    while (exp > 0) {
        if (exp % 2 == 1L) res = (res * base) % m
        base = (base * base) % m
        exp /= 2
    }
    return res
}

fun modInverse(n: Long, m: Long): Long {
    return power(n, m - 2, m)
}

fun solve() {
    val fr = FastReader(System.`in`)
    val out = PrintWriter(System.out)
    val MOD = 998244353L

    val nextT = fr.next() ?: return
    val t = nextT.toInt()
    
    val pow2 = LongArray(200005)
    pow2[0] = 1L
    for (i in 1 until pow2.size) pow2[i] = (pow2[i - 1] * 2) % MOD
    
    val inv2 = LongArray(200005)
    inv2[0] = 1L
    val i2 = modInverse(2L, MOD)
    for (i in 1 until inv2.size) inv2[i] = (inv2[i - 1] * i2) % MOD

    repeat(t) {
        val n = fr.nextInt()
        val a = IntArray(n) { fr.nextInt() }
        
        var totalZ = 0
        for (x in a) if (x == 0) totalZ++
        
        var ans = pow2[totalZ]
        
        val posMap = mutableMapOf<Int, MutableList<Int>>()
        var curZ = 0
        for (i in 0 until n) {
            if (a[i] == 0) {
                curZ++
            } else {
                posMap.getOrPut(a[i]) { mutableListOf() }.add(curZ)
            }
        }
        
        for (positions in posMap.values) {
            if (positions.size < 2) continue
            
            var prefixSumPow = 0L
            for (j in 0 until positions.size) {
                val L = positions[j]
                // Contribution for all i < j: sum_{i < j} 2^L_i * 2^(totalZ - L_j)
                val term = (prefixSumPow * pow2[totalZ - L]) % MOD
                ans = (ans + term) % MOD
                
                prefixSumPow = (prefixSumPow + pow2[L]) % MOD
            }
        }
        
        out.println(ans)
    }
    out.flush()
}

fun main() {
    solve()
}
