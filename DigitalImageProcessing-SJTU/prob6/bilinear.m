function result_gray = bilinear(input,m,n,type,params)
    [M,N] = size(input);
    if strcmp(type,'scale')
        m_value = m/params('cy');
        n_value = n/params('cx');
    elseif strcmp(type,'trans')
        m_value = m-params('ty');
        n_value = n-params('tx');
    end
    
    lt_pos = [min(M,max(1,floor(m_value))),min(N,max(1,floor(n_value)))];
    ld_pos = [max(1,min(M,ceil(m_value))),min(N,max(1,floor(n_value)))];
    rt_pos = [min(M,max(1,floor(m_value))),max(1,min(N,ceil(n_value)))];
    rd_pos = [max(1,min(M,ceil(m_value))),max(1,min(N,ceil(n_value)))];
    [lt_gray,ld_gray,rt_gray,rd_gray] = deal(input(lt_pos(1),lt_pos(2)),...
        input(ld_pos(1),ld_pos(2)),input(rt_pos(1),rt_pos(2)),input(rd_pos(1),rd_pos(2)));
    top_gray = (n_value-lt_pos(2))/(rt_pos(2)-lt_pos(2))*(rt_gray-lt_gray)+lt_gray;
    down_gray = (n_value-lt_pos(2))/(rt_pos(2)-lt_pos(2))*(rd_gray-ld_gray)+ld_gray;
    result_gray = (ld_pos(1)-m_value)/(ld_pos(1)-lt_pos(1))*(top_gray-down_gray)+down_gray;
end
